# DDS control-surface excitation

## Architecture decision (before implementation)

Fixed-wing GUIDED navigation and stabilization remain responsible for the baseline.
The existing ArduPlane/systemid.cpp is QuadPlane-only and modifies its attitude/rate/
actuator controllers; it is not reused as the fixed-wing injection path.

Excitation is mixed independently with the same scaled mixer arithmetic as baseline
outputs. Each physical SRV_Channel converts its mixed perturbation using its live
MIN/MAX/TRIM/REVERSED calibration, subtracts trim, adds the delta to baseline PWM,
and clamps to calibration bounds. This preserves the specified asymmetric physical
percentage semantics, unlike adding logical commands before a nonlinear calibration.
The hook belongs inside calc_pwm, after normal override/emergency-stop precedence.
It never uses set_output_pwm as an override. Excitation buffers are cycle-local.

Commands enter through AP_ExternalControl and a bounded mailbox. Only the flight
loop decides authorization and modifies outputs. DDS callbacks do not change servos.
Startup requires a valid disable followed by enable. Operation requires airborne,
armed, safety-off fixed-wing GUIDED, normal flight stage, and no failsafe/conflicting
output control. Timeout/command-disable returns to baseline within a bounded interval;
loss of flight authorization removes excitation immediately.

Conventional, repeated functions, flaperon, V-tail and elevon mappings are supported.
Unsupported custom/scripted surface mappings and differential spoilers are rejected.
No throttle perturbation or RC override is used. Existing integrators are not reset;
their anti-windup cannot directly observe added output saturation. Closed-loop response
is therefore measured, not open-loop aerodynamics. Logged PWM is commanded output,
not measured actuator position. SITL is not physical-flight qualification.

Firmware timestamps share AP DDS time (RTC when available, boot time otherwise);
monotonic receipt timestamps independently enforce freshness. Clock discontinuities
invalidate authorization. One publisher per vehicle is required; DDS sequence numbers
are not authentication.

## Verification gates

1. Trace baseline and mixer paths; capture disabled SITL baseline.
2. Test calibration, mixing, state transitions and override precedence; build firmware.
3. Test DDS wire delivery, ordering, invalid samples and freshness.
4. Test ros2_sid mission waveform, timing, units, RC gate and stop paths.
5. Run conventional and mixed-airframe SITL constant/chirp/multisine experiments.
6. Verify DataFlash completeness and independent expected-versus-final PWM assertions;
   produce aligned command/actuator/response plots and machine-readable reports.
7. Execute documented commands and validate C4 diagrams against code.

A blocked or failed check is not a passed gate. No physical aircraft testing.

## ROS-native evidence

The coherent `/ap/sid/output` snapshot is the preferred plotting input. It includes
firmware boot/clock timestamps, requested/applied axes, per-servo baseline/final PWM,
current calibration, clipping, mode, attitude (rad), body rates (rad/s), and airspeed.
Record it together with command/status/time topics using rosbag2. The offline plotter
reads bags directly and does not replay control commands onto a live network.
DataFlash remains a separate cross-check and records every enabled flight-loop cycle;
DDS telemetry is latest-sample, up to 50 Hz, and can drop samples. A bag cannot prove
that every flight-loop output was delivered over DDS.

## Optional straight-flight ROS coordinator

`ros2_sid.straight_flight.StraightFlight` is a component of the existing mission
process, enabled by default for DDS missions. `--straight-flight PATH` overrides the
packaged settings and `--no-straight-flight` explicitly disables coordination. It sends acknowledged fixed course,
relative-altitude, and airspeed targets through MAVROS. It gates waveform start
on fresh telemetry and a continuous settling dwell, then leaves those targets
unchanged while the DDS perturbation runs. This does not change the firmware
injection path or replace ArduPlane guidance/stabilization.

```mermaid
flowchart LR
  Operator[Operator: select/start/stop/quit] --> Mission[ros2_sid mission process]
  subgraph MissionComponents[Components inside mission process]
    Coordinator[StraightFlight: settle and recover]
    Sampler[Existing CSV / waveform sampler]
    Coordinator -->|READY gate| Sampler
  end
  Mission --> Coordinator
  Coordinator -->|Targets and recovery mode| MAVROS[MAVROS command services]
  MAVROS -->|MAVLink| Guidance[ArduPlane normal GUIDED controller]
  Sampler -->|Normalized perturbations| DDS[AP_DDS through XRCE agent]
  Guidance --> Outputs[Existing mixer and calibrated additive outputs]
  DDS --> Outputs
  Outputs -->|Applied output and response| Coordinator
  Coordinator --> Events[/sid/straight_flight events]
  Events --> Bag[rosbag2 and offline validation]
  Outputs --> Bag
```

On exit the sampler is revoked, DDS disable is repeated, and fresh zero applied
contribution is observed before requesting LOITER. Actual vehicle mode confirms
recovery. Operator/failsafe modes and disarm take precedence; a missing handoff
confirmation is reported rather than assumed. Process/host failure can prevent
navigation recovery even though firmware command timeout removes excitation.
See the [operator guide](../../../ros2_sid/ros2_sid/docs/straight_flight_plan.md)
and [executed verification](VERIFICATION.md) for settings, exact limits, and tests.
