#pragma once
// Transport-independent state and mixer arithmetic. Times are monotonic microseconds.
#include <stdint.h>
#include <cmath>
#include <algorithm>

namespace SurfaceExcitation {
inline float bound(float x, float lo, float hi) { return std::max(lo, std::min(x, hi)); }
inline void mix(float in1, float in2, float offset, float gain, float &left, float &right)
{
    if (offset < 0) { in2 *= (100-offset)*0.01f; }
    else if (offset > 0) { in1 *= (100+offset)*0.01f; }
    left = bound((in2-in1)*gain, -4500, 4500);
    right = bound((in2+in1)*gain, -4500, 4500);
}
struct Command {
    uint32_t sequence{};
    uint64_t stamp_us{}, received_us{};
    bool enable{};
    float axis[3]{};
};
struct Status {
    uint8_t state{}, reason{};
    uint32_t sequence{}, revision{}, clips{};
    float requested[3]{}, applied[3]{};
};
struct Output {
    uint64_t time_us{}, clock_us{};
    Status status{};
    uint8_t count{}, mode{};
    bool accepted{};
    float gain{}, offset{}, attitude[3]{}, rates[3]{}, airspeed{};
    int16_t function[32]{}, delta[32]{};
    uint16_t minimum[32]{}, trim[32]{}, maximum[32]{}, baseline[32]{}, pwm[32]{};
    uint8_t reversed[32]{}, clipped[32]{};
    float excitation[32]{};
};
enum State : uint8_t { DISABLED, ARMED, ACTIVE, TIMEOUT, FAULT };
enum Reason : uint8_t { NONE, UNAUTHORIZED, INVALID, STALE, ORDER, CONFIG, CLOCK, DISCONNECTED, OVERRIDE };
struct Settings {
    float maximum[3]{0.1f,0.1f,0.1f};
    float physical_max{0.2f}, slew{0};
    uint32_t timeout_us{200000}, return_us{200000};
    bool valid() const {
        for (float v : maximum) { if (!std::isfinite(v) || v < 0 || v > 1) { return false; } }
        return std::isfinite(physical_max) && physical_max > 0 && physical_max <= 1 &&
            std::isfinite(slew) && slew >= 0 && slew <= 100 &&
            timeout_us >= 20000 && timeout_us <= 2000000 && return_us <= 2000000;
    }
};
class Engine {
public:
    Status status{};
    void disable() { fault(NONE); status.state = DISABLED; }
    void fault(Reason why) {
        status.state = FAULT; status.reason = why; ready = false; running = false; ramping = false;
        for (float &v : status.applied) { v = 0; }
    }
    bool accept(const Command &c, uint64_t clock_us, uint64_t now, const Settings &s) {
        if (!s.valid()) { fault(CONFIG); return false; }
        for (float v : c.axis) {
            if (!std::isfinite(v) || fabsf(v)>1) { status.reason = INVALID; return false; }
        }
        // Allow at most 20 ms clock estimation error into the future.
        if (!c.stamp_us || c.stamp_us > clock_us+20000 ||
            (clock_us > c.stamp_us && clock_us-c.stamp_us > s.timeout_us) ||
            now < c.received_us || now-c.received_us > s.timeout_us) {
            status.reason = STALE; return false;
        }
        if (!c.enable) {
            // A fresh disable establishes a new publisher sequence epoch.
            begin_return(now, s, DISABLED);
            ready = true; have_sequence = true; status.sequence = c.sequence;
            return true;
        }
        const uint32_t difference = c.sequence-status.sequence;
        if (!ready || (have_sequence && (difference == 0 || difference >= 0x80000000U))) {
            status.reason = ORDER; return false;
        }
        have_sequence = true; status.sequence = c.sequence; last_received = c.received_us;
        status.clips = 0;
        for (uint8_t i=0; i<3; i++) {
            status.requested[i] = c.axis[i];
            target[i] = bound(c.axis[i], -s.maximum[i], s.maximum[i]);
            if (fabsf(target[i] - c.axis[i]) > 1.0e-7f) { status.clips |= 1U<<i; }
        }
        running = true; ramping = false; status.state = ACTIVE; status.reason = NONE;
        return true;
    }
    void tick(uint64_t now, bool authorized, const Settings &s) {
        const float dt = last_tick && now>=last_tick ? (now-last_tick)*1.0e-6f : 0;
        last_tick = now;
        if (!authorized || !s.valid()) { fault(authorized ? CONFIG : UNAUTHORIZED); return; }
        if (running && now-last_received > s.timeout_us) {
            begin_return(now, s, TIMEOUT); ready = false; status.reason = STALE;
        }
        if (ramping) {
            const float factor = s.return_us ? std::max(0.0f, 1.0f-float(now-ramp_start)/s.return_us) : 0;
            for (uint8_t i=0; i<3; i++) { status.applied[i] = ramp_from[i]*factor; }
            if (factor <= 0) { ramping = false; }
        } else if (running) {
            for (uint8_t i=0; i<3; i++) {
                target[i] = bound(target[i], -s.maximum[i], s.maximum[i]);
                status.applied[i] = s.slew > 0 ? bound(target[i], status.applied[i]-s.slew*dt, status.applied[i]+s.slew*dt) : target[i];
                status.applied[i] = bound(status.applied[i], -s.maximum[i], s.maximum[i]);
            }
        } else if (ready) { status.state = ARMED; }
    }
    bool output_active() const { return running || ramping; }
private:
    void begin_return(uint64_t now, const Settings &s, State state) {
        if (!ramping) {
            for (uint8_t i=0; i<3; i++) { ramp_from[i] = status.applied[i]; }
            ramp_start = now;
        }
        bool nonzero = false;
        for (float v : status.applied) { nonzero |= fabsf(v) > 1.0e-7f; }
        ramping = s.return_us > 0 && nonzero; running = false; status.state = state;
        if (!ramping) { for (float &v : status.applied) { v = 0; } }
    }
    bool ready{}, running{}, ramping{}, have_sequence{};
    uint64_t last_received{}, last_tick{}, ramp_start{};
    float target[3]{}, ramp_from[3]{};
};
}
