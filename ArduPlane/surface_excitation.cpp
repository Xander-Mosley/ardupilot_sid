#include "Plane.h"
#include <AP_RTC/AP_RTC.h>
#include "surface_excitation.h"

extern const AP_HAL::HAL& hal;

using namespace SurfaceExcitation;
const AP_Param::GroupInfo PlaneSurfaceExcitation::var_info[] = {
    // @Param: ENABLE
    // @DisplayName: External surface excitation enable
    // @Description: Allow explicitly authorized GUIDED surface experiments. Airborne operation is required unless GND_TEST is enabled. A fresh disable then enable command is still required.
    // @Values: 0:Disabled,1:Enabled
    // @User: Advanced
    AP_GROUPINFO_FLAGS("ENABLE", 1, PlaneSurfaceExcitation, enabled, 0, AP_PARAM_FLAG_ENABLE),
    // @Param: R_MAX
    // @DisplayName: Maximum roll excitation
    // @Description: Per-axis roll bound as a fraction of calibrated deflection.
    // @Range: 0 1
    // @User: Advanced
    AP_GROUPINFO("R_MAX", 2, PlaneSurfaceExcitation, max_roll, 0.1f),
    // @Param: P_MAX
    // @DisplayName: Maximum pitch excitation
    // @Description: Per-axis pitch bound as a fraction of calibrated deflection.
    // @Range: 0 1
    // @User: Advanced
    AP_GROUPINFO("P_MAX", 3, PlaneSurfaceExcitation, max_pitch, 0.1f),
    // @Param: Y_MAX
    // @DisplayName: Maximum yaw excitation
    // @Description: Per-axis yaw bound as a fraction of calibrated deflection.
    // @Range: 0 1
    // @User: Advanced
    AP_GROUPINFO("Y_MAX", 4, PlaneSurfaceExcitation, max_yaw, 0.1f),
    // @Param: S_MAX
    // @DisplayName: Maximum mixed surface excitation
    // @Description: Bound on each mixed physical surface before calibration conversion.
    // @Range: 0.001 1
    // @User: Advanced
    AP_GROUPINFO("S_MAX", 5, PlaneSurfaceExcitation, max_surface, 0.2f),
    // @Param: TIMEOUT
    // @DisplayName: Excitation command timeout
    // @Description: Maximum source and receipt age in milliseconds before bounded return.
    // @Range: 20 2000
    // @User: Advanced
    AP_GROUPINFO("TIMEOUT", 6, PlaneSurfaceExcitation, timeout_ms, 200),
    // @Param: RETURN
    // @DisplayName: Excitation return duration
    // @Description: Maximum milliseconds to remove excitation on timeout or command disable. Mode loss removes it immediately.
    // @Range: 0 2000
    // @User: Advanced
    AP_GROUPINFO("RETURN", 7, PlaneSurfaceExcitation, return_ms, 200),
    // @Param: SLEW
    // @DisplayName: Excitation slew rate
    // @Description: Maximum normalized axis change per second. Zero disables active-command slew limiting.
    // @Range: 0 100
    // @User: Advanced
    AP_GROUPINFO("SLEW", 8, PlaneSurfaceExcitation, slew, 0),
    // @Param: GND_TEST
    // @DisplayName: Surface excitation ground test
    // @Description: Permit grounded excitation while disarmed or armed instead of airborne normal-flight excitation. Requires ENABLE, GUIDED and safety off; all failsafe and output limits remain enforced. Isolate propulsion before use and restore zero before flight.
    // @Values: 0:Airborne only,1:Ground only
    // @User: Advanced
    AP_GROUPINFO("GND_TEST", 9, PlaneSurfaceExcitation, ground_test, 0),
    AP_GROUPEND
};
Settings PlaneSurfaceExcitation::settings() const
{
    Settings s;
    s.maximum[0]=max_roll; s.maximum[1]=max_pitch; s.maximum[2]=max_yaw;
    s.physical_max=max_surface; s.slew=slew;
    s.timeout_us=uint32_t(timeout_ms.get())*1000U; s.return_us=uint32_t(return_ms.get())*1000U;
    return s;
}
void PlaneSurfaceExcitation::submit(const Command &command)
{
    WITH_SEMAPHORE(sem);
    // Preserve a disable edge until consumed; enabled samples may be dropped.
    if (!disable_pending || !command.enable) {
        pending=command; pending.received_us=AP_HAL::micros64(); have_pending=true;
        disable_pending=!command.enable;
    }
}
void PlaneSurfaceExcitation::disconnect()
{
    WITH_SEMAPHORE(sem);
    disconnected=true; have_pending=false; disable_pending=false;
}
Status PlaneSurfaceExcitation::get_status()
{
    WITH_SEMAPHORE(sem);
    return published;
}
Output PlaneSurfaceExcitation::get_output()
{
    WITH_SEMAPHORE(sem);
    return published_output;
}
void PlaneSurfaceExcitation::prepare(float *outputs)
{
    const uint64_t now=AP_HAL::micros64();
    uint64_t clock;
    if (!AP::rtc().get_utc_usec(clock)) { clock=now; }
    const Settings s=settings();
    Command command{};
    bool received, lost;
    {
        WITH_SEMAPHORE(sem);
        received=have_pending; command=pending; lost=disconnected;
        have_pending=false; disable_pending=false; disconnected=false;
    }
    const bool flying=plane.is_flying();
    const bool flight_ready=(ground_test.get()==1 && !flying) ||
        (ground_test.get()==0 && flying &&
         plane.flight_stage==AP_FixedWing::FlightStage::NORMAL);
    // Excitation is independent of arming. Never bypass hardware safety;
    // the normal servo path retains its separate disarmed throttle handling.
    const bool safety_ready=
        hal.util->safety_switch_state()!=AP_HAL::Util::SAFETY_DISARMED;
    bool authorized=enabled.get()==1 && plane.control_mode==&plane.mode_guided &&
        safety_ready && flight_ready &&
        !plane.any_failsafe_triggered() && !plane.rc_failsafe_active() &&
        !SRV_Channels::get_emergency_stop() && !plane.g2.servo_channels.auto_trim_enabled();
#if HAL_QUADPLANE_ENABLED
    // Fixed-wing-only v1. QuadPlane configurations are conservatively excluded.
    authorized=authorized && !plane.quadplane.enabled();
#endif
#if AP_PLANE_SYSTEMID_ENABLED
    authorized=authorized && !plane.g2.systemid.is_running();
#endif
#if AP_SCRIPTING_ENABLED
    authorized=authorized && !plane.nav_scripting_active();
#endif
    const bool clock_jump=last_mono &&
        (clock < last_clock || llabs(int64_t(clock-last_clock)-int64_t(now-last_mono))>50000);
    last_clock=clock; last_mono=now;

    // Hash the live configuration, including all physical assignments and mixing.
    uint32_t hash=2166136261U;
    auto add=[&hash](uint32_t v) { hash=(hash^v)*16777619U; };
    uint32_t gain_bits;
    const float gain=plane.g.mixing_gain;
    memcpy(&gain_bits, &gain, sizeof(gain_bits)); add(gain_bits); add(plane.g.mixing_offset);
    bool valid=s.valid() && isfinite(gain) && gain>=0 && gain<=2;
    uint8_t axes=0;
    for (uint8_t i=0; i<NUM_SERVO_CHANNELS; i++) {
        const auto *ch=SRV_Channels::srv_channel(i);
        const auto f=ch->get_function();
        add(f); add(ch->get_output_min()); add(ch->get_trim()); add(ch->get_output_max()); add(ch->get_reversed());
        uint8_t mask=0;
        switch (f) {
        case SRV_Channel::k_aileron: case SRV_Channel::k_flaperon_left: case SRV_Channel::k_flaperon_right: mask=1; break;
        case SRV_Channel::k_elevator: mask=2; break;
        case SRV_Channel::k_rudder: mask=4; break;
        case SRV_Channel::k_elevon_left: case SRV_Channel::k_elevon_right: mask=3; break;
        case SRV_Channel::k_vtail_left: case SRV_Channel::k_vtail_right: mask=6; break;
        default:
            if ((SRV_Channel::is_control_surface(f) && f!=SRV_Channel::k_flap && f!=SRV_Channel::k_flap_auto) ||
                (f>=SRV_Channel::k_scripting1 && f<=SRV_Channel::k_scripting16)) { valid=false; }
            break;
        }
        if (mask) {
            axes|=mask;
            valid=valid && ch->get_output_min()<ch->get_trim() && ch->get_trim()<ch->get_output_max();
        }
    }
    const bool changed=configured && hash!=config_hash;
    if (!configured || changed) {
        configured=true; config_hash=hash; revision++;
    }
#if HAL_LOGGING_ENABLED
    // Startup records can precede logger readiness. Repeat the live calibration
    // while enabled so every flight log can reconstruct the actuator deltas.
    if (enabled.get()==1 && (changed || now-last_config_log>=1000000)) {
        last_config_log=now;
        for (uint8_t i=0; i<NUM_SERVO_CHANNELS; i++) {
            const auto *ch=SRV_Channels::srv_channel(i);
            AP::logger().WriteStreaming("SXCF", "TimeUS,Rev,Ch,Fn,Min,Trim,Max,Revrs,Gain,Offset", "QIBhHHHBfb",
                now, revision, i, int16_t(ch->get_function()), ch->get_output_min(), ch->get_trim(), ch->get_output_max(),
                uint8_t(ch->get_reversed()), double(gain), int8_t(plane.g.mixing_offset));
        }
    }
#endif
    engine.status.revision=revision;
    if (enabled.get()==0) {
        engine.disable();
    } else if (!authorized || !valid || changed || lost || clock_jump) {
        engine.fault(!authorized ? UNAUTHORIZED : (!valid || changed) ? CONFIG : lost ? DISCONNECTED : CLOCK);
    } else {
        if (received) {
            bool mapped=true;
            for (uint8_t i=0; i<3; i++) {
                if (!is_zero(command.axis[i]) && !(axes & (1U<<i))) { mapped=false; }
            }
            bool accepted=false;
            if (!mapped && command.enable) { engine.fault(CONFIG); }
            else { accepted=engine.accept(command, clock, now, s); }
#if HAL_LOGGING_ENABLED
            AP::logger().WriteStreaming("SXC", "TimeUS,Stamp,Recv,Seq,En,R,P,Y,Valid", "QQQIBfffB",
                now, command.stamp_us, command.received_us, command.sequence, uint8_t(command.enable),
                double(command.axis[0]), double(command.axis[1]), double(command.axis[2]), uint8_t(accepted));
#endif
        }
        engine.tick(now, true, s);
    }
    if (!engine.output_active()) { return; }
    const auto &a=engine.status.applied;
    float el,er,vr,vl;
    mix(a[0]*4500,a[1]*4500,plane.g.mixing_offset,gain,el,er);
    mix(a[2]*4500,a[1]*4500,plane.g.mixing_offset,gain,vr,vl);
    for (uint8_t i=0; i<NUM_SERVO_CHANNELS; i++) {
        float v=0;
        switch (SRV_Channels::srv_channel(i)->get_function()) {
        case SRV_Channel::k_aileron: case SRV_Channel::k_flaperon_left: case SRV_Channel::k_flaperon_right: v=a[0]*4500; break;
        case SRV_Channel::k_elevator: v=a[1]*4500; break;
        case SRV_Channel::k_rudder: v=a[2]*4500; break;
        case SRV_Channel::k_elevon_left: v=el; break;
        case SRV_Channel::k_elevon_right: v=er; break;
        case SRV_Channel::k_vtail_right: v=vr; break;
        case SRV_Channel::k_vtail_left: v=vl; break;
        default: break;
        }
        outputs[i]=bound(v, -s.physical_max*4500, s.physical_max*4500);
        if (!is_equal(outputs[i],v)) { engine.status.clips|=8; }
    }
}
void PlaneSurfaceExcitation::finish(const float *outputs, bool accepted)
{
    const uint64_t now=AP_HAL::micros64();
    const bool active=engine.output_active();
    if (!accepted && active) { engine.fault(OVERRIDE); }
    auto &st=engine.status;
#if HAL_LOGGING_ENABLED
    if (enabled.get()==1) {
        AP::logger().WriteStreaming("SXA", "TimeUS,Seq,R,P,Y,BR,BP,BY", "QIffffff",
            now, st.sequence, double(st.applied[0]), double(st.applied[1]), double(st.applied[2]),
            double(SRV_Channels::get_output_scaled(SRV_Channel::k_aileron)),
            double(SRV_Channels::get_output_scaled(SRV_Channel::k_elevator)),
            double(SRV_Channels::get_output_scaled(SRV_Channel::k_rudder)));
        for (uint8_t i=0; i<NUM_SERVO_CHANNELS; i++) {
            const auto *ch=SRV_Channels::srv_channel(i);
            if (!SRV_Channel::is_control_surface(ch->get_function())) { continue; }
            const auto &r=ch->excitation_result;
            if (r.clipped) { st.clips|=16; }
            AP::logger().WriteStreaming("SXO", "TimeUS,Seq,Rev,Ch,Fn,U,Base,Want,Delta,PWM,Clip,OK", "QIIBhfHhhHBB",
                now, st.sequence, revision, i, int16_t(ch->get_function()), double(outputs[i]/4500),
                r.baseline, r.requested_delta, r.applied_delta, ch->get_output_pwm(), uint8_t(r.clipped), uint8_t(accepted));
        }
    }
    if (last_state!=st.state || last_reason!=st.reason) {
        AP::logger().WriteStreaming("SXS", "TimeUS,State,Reason,Seq,Rev,Mode", "QBBIIB",
            now, st.state, st.reason, st.sequence, revision, uint8_t(plane.control_mode->mode_number()));
    }
#endif
    last_state=st.state; last_reason=st.reason;
    Output snapshot{};
    snapshot.time_us=now; snapshot.clock_us=last_clock; snapshot.status=st;
    snapshot.count=NUM_SERVO_CHANNELS; snapshot.mode=uint8_t(plane.control_mode->mode_number());
    snapshot.accepted=accepted;
    snapshot.gain=plane.g.mixing_gain; snapshot.offset=plane.g.mixing_offset;
    snapshot.attitude[0]=plane.ahrs.get_roll(); snapshot.attitude[1]=plane.ahrs.get_pitch(); snapshot.attitude[2]=plane.ahrs.get_yaw();
    const Vector3f gyro=plane.ahrs.get_gyro();
    snapshot.rates[0]=gyro.x; snapshot.rates[1]=gyro.y; snapshot.rates[2]=gyro.z;
    snapshot.airspeed=plane.smoothed_airspeed;
    for (uint8_t i=0; i<NUM_SERVO_CHANNELS; i++) {
        const auto *ch=SRV_Channels::srv_channel(i);
        snapshot.function[i]=int16_t(ch->get_function());
        snapshot.minimum[i]=ch->get_output_min(); snapshot.trim[i]=ch->get_trim(); snapshot.maximum[i]=ch->get_output_max();
        snapshot.reversed[i]=ch->get_reversed(); snapshot.excitation[i]=outputs[i]/4500;
        snapshot.baseline[i]=ch->excitation_result.baseline; snapshot.pwm[i]=ch->get_output_pwm();
        snapshot.delta[i]=ch->excitation_result.applied_delta; snapshot.clipped[i]=ch->excitation_result.clipped;
    }
    WITH_SEMAPHORE(sem);
    published=st; published_output=snapshot;
}
