# Implementation and verification record

## Delivered implementation

See [architecture](ARCHITECTURE.md), [usage/build/launch instructions](README.md),
and the [modified-file inventory](MODIFIED_FILES.txt). C4 context, container and
component diagrams are available as SVG/PNG with editable `render_c4.py` source.

GUIDED stabilization and baseline surface mixing continue normally. The Plane-owned
engine computes separate logical perturbations with the existing mixer arithmetic.
`SRV_Channel::calc_pwm()` uses live MIN/MAX/TRIM/REVERSED values to convert each
physical contribution, add it to baseline PWM, and constrain the result. Zero
perturbation preserves the original path. Overrides/emergency stop take precedence;
a conflicting override rejects the whole excitation vector. No raw PWM command is
exposed. Conventional, duplicated, flaperon, V-tail and elevon functions are mapped;
unsupported control-surface/scripted functions inhibit activation.

`ControlSurfaceExcitation` carries sequence, enable, AP-clock stamp and normalized
roll/pitch/yaw on `/ap/sid/control_surface`. Status and coherent physical-output
snapshots use `/ap/sid/status` and `/ap/sid/output`. DataFlash records commands,
state, baseline/applied outputs, clipping and live calibration. The ROS publisher
belongs to `ros2_sid`; both existing mission entrypoints select it with
`--interface dds`. Legacy trajectory behavior is retained.

The ROS modules have documented, typed public interfaces, named firmware states,
validated waveform specifications and standard formatting. See
`ros2_sid/ros2_sid/README_surface_excitation.md` in the outer workspace for quality
checks. Multisine examples include roll with pitch/yaw offsets and independent
multisines on all three axes. Mission selection uses the existing SITL/HITL scripts.

## Executed checks

| Check | Result |
|---|---|
| ArduPlane SITL, DDS enabled | Build passed, including the final configuration-logging fix |
| ArduPlane SITL, DDS disabled | Build passed after the same fix |
| Standalone C++ engine | Assertions passed with `-Wall -Wextra -Werror` |
| Real SRV_Channel gtests | Four passed: calibrated addition/no latch, asymmetry/reversal, saturation/duplicates/E-stop, whole-vector override rejection |
| Existing DDS tests | Time conversion and external odometry tests passed |
| ROS interfaces and publisher | `colcon build` passed |
| Plane launch package | Plane-only prebuilt-firmware installation passed; installed launch arguments resolve model/default parameter files |
| Python/ROS regressions | 21 pytest cases passed, none skipped |
| Colcon/CTest registration | 24 reported results: 21 cases plus three CTest wrappers; no errors, failures or skips |
| Python style | Ruff 0.17.1 formatting, lint, annotation and docstring checks passed |
| Python typing | Mypy 2.4.0 strict checks passed with documented external ROS import/subclass allowances |

Engine tests cover startup authorization, limits, invalid/stale/ordered samples,
wraparound, timeout/disable ramps, simultaneous axes, authorization loss, and
clock/disconnect/config/override fault reactivation. ROS tests cover waveform math,
combined multisine bounds, independent axes, cadence, stale/jumping clocks, RC gating,
shutdown, publisher-restart acknowledgment and offline validation failures.

## Final airborne SITL experiments

All three final runs completed normal takeoff and airborne fixed-wing GUIDED with
firmware safety gates enabled. Each ran a 10-second chirp, 12-second roll multisine,
and 20-second independent three-axis multisine, followed by the safety probe.

| Airframe / retained directory | Publish rate | Actuator samples | Maximum PWM reconstruction error | Exact bag/DataFlash matches | Applied spans: chirp / roll multisine / three-axis multisine |
|---|---:|---:|---:|---:|---|
| `conventional_50hz` | 50 Hz | 9,618 | 1 µs | 9,618 / 9,618 | 9.94 / 11.96 / 19.96 s |
| `vtail_acknowledged` | 100 Hz | 9,669 | 1 µs | 9,669 / 9,669 | 9.96 / 11.94 / 19.94 s |
| `elevon_50hz` | 50 Hz | 9,638 | 1 µs | 9,638 / 9,638 | 9.98 / 11.96 / 19.94 s |

No calibration was missing. Accepted-sequence logical axes matched the publisher
CSV without mismatches. Active coverage exceeded 99.7% of observed waveform frames;
maximum observed active-frame gaps were below 41 ms. Bag/DataFlash matching checks
firmware timestamp, channel, sequence, revision, baseline, actual delta and final PWM.
The independent physical reconstruction uses calibration/reversal and baseline,
with at most one microsecond of integer-conversion difference. The live probe
independently checks the mixer equations before checking calibrated output.

The safety probe passed on each final airframe: simultaneous calibrated outputs,
duplicate-command timeout, stale timestamps, nonfinite/out-of-range values,
explicit disable, silence timeout, mode-change removal, live duplicated-channel
mapping/calibration/reversal, and invalid-calibration inhibition. The controller
continues producing baseline outputs throughout. Unit tests verify the disabled
servo path exactly; aircraft trajectories are not compared after excitation.

A separate DataFlash-only reconstruction of `vtail_combined` passed for 29,398
actuator samples, with maximum PWM error 1 µs and complete configuration. This
checks firmware logging independently of the bag but does not make that older run
a successful complete-waveform experiment (see below).

## Individual-axis chirp and multisine flights

Six new conventional-airframe SITL experiments were executed sequentially in airborne
GUIDED, at simulation speed 1 and 50 Hz publication. Only the named axis was excited;
the other two normalized commands, applied logical excitations and physical PWM
perturbations were verified to be zero throughout each plotted experiment window.
Normal controller outputs and cross-axis aircraft responses remain present.

- **Chirps:** 0.10 normalized amplitude, linear sweep from 0.2 to 3 Hz over 10 s.
- **Multisines:** 0.5, 1 and 2 Hz components; amplitudes 0.03, 0.03 and 0.04;
  phases 0, 1 and 2 radians; 12 s duration. The sum-of-amplitudes bound is 0.10.
- **Validation:** all six full-duration/accepted-sequence checks passed. All 14,608
  actuator samples in the complete recording matched DataFlash exactly, with
  independent calibrated-PWM reconstruction error at most 1 µs and no missing
  calibration. The recording also contains the subsequent safety probe, which passed.
- **Retained data:** `sid_results/individual_axes/` in the outer workspace contains
  the ROS bag, DataFlash log, six exact waveform JSON files, command CSVs, process
  logs, and aggregate `plots/report.json`. Figures below are saved with this report
  as PNG/PDF; [plot summary](figures/individual_axes/summary.json) records the
  per-experiment zero-other-axis checks; the [validation report](figures/individual_axes/validation.json) retains the numerical acceptance results.

| Experiment | Observed active span | Active observed frames | Maximum output-frame gap | Result |
|---|---:|---:|---:|---|
| chirp roll | 9.960 s | 100.00% | 40.82 ms | Passed |
| multisine roll | 11.960 s | 100.00% | 39.98 ms | Passed |
| chirp pitch | 9.940 s | 100.00% | 39.98 ms | Passed |
| multisine pitch | 11.939 s | 99.81% | 39.98 ms | Passed |
| chirp yaw | 9.940 s | 100.00% | 40.82 ms | Passed |
| multisine yaw | 11.939 s | 100.00% | 40.82 ms | Passed |

Each figure shows requested versus applied logical excitation, actual additive PWM
on all three control surfaces, all three body angular rates, and the selected-axis
attitude change. Time is aligned using the firmware/AP clock. Vertical lines mark
the first and last enabled command samples; the following interval shows removal
of the perturbation. Attitude is unwrapped and referenced to the first plotted
sample. GUIDED's nominal motion has not been subtracted, and rates/angles are
recorded responses rather than a claim of isolated open-loop dynamics.

### Roll only

![Roll chirp: command, applied PWM and flight response](figures/individual_axes/chirp_roll.png)

[Download roll chirp PDF](figures/individual_axes/chirp_roll.pdf)

![Roll multisine: command, applied PWM and flight response](figures/individual_axes/multisine_roll.png)

[Download roll multisine PDF](figures/individual_axes/multisine_roll.pdf)

### Pitch only

![Pitch chirp: command, applied PWM and flight response](figures/individual_axes/chirp_pitch.png)

[Download pitch chirp PDF](figures/individual_axes/chirp_pitch.pdf)

![Pitch multisine: command, applied PWM and flight response](figures/individual_axes/multisine_pitch.png)

[Download pitch multisine PDF](figures/individual_axes/multisine_pitch.pdf)

### Yaw only

![Yaw chirp: command, applied PWM and flight response](figures/individual_axes/chirp_yaw.png)

[Download yaw chirp PDF](figures/individual_axes/chirp_yaw.pdf)

![Yaw multisine: command, applied PWM and flight response](figures/individual_axes/multisine_yaw.png)

[Download yaw multisine PDF](figures/individual_axes/multisine_yaw.pdf)

Reproduce the flights with the runner's `--individual-axes --rate 50` options.
Replot the same bag using `python3 -m ros2_sid.surface_axis_plots --run RUN_DIRECTORY
--output FIGURE_DIRECTORY` after sourcing the ROS workspace; detailed commands are
in `ros2_sid/ros2_sid/README_surface_excitation.md` in the outer workspace.

## Artifacts and reproducibility

All paths below are relative to the outer workspace; large artifacts are excluded
from version control and retained locally under `sid_results/`.

Each final directory contains the ROS bag, firmware `.BIN`, publisher command CSVs,
launch/process logs, `execution.json`, and `plots/` with PNG/PDF figures, actuator
CSV, aligned response CSV and `report.json`. The final conventional/elevon runner
also retains merged parameter defaults and exact waveform JSON. The V-tail run
used the checked-in 100 Hz examples. Build and ROS-test logs are retained in
`sid_results/verification/`.

The README supplies exact Waf, colcon, launch, bag-record and replot commands.
Tests used ROS Humble, domain 41, UDP agent port 2021 and the UDP-only Fast DDS
profile. Simulation speed was 1. No physical devices were mapped or aircraft flown.

Earlier runs are retained as failed/diagnostic evidence. A publisher-restart race
allowed an old ARMED status to bypass the new disable acknowledgment; the
`vtail_combined` roll multisine applied only 1.68 of 12 seconds. It is **not** a
complete-maneuver pass despite correct scaling. The publisher now acknowledges its
own randomized sequence epoch, and duration/axis checks reject this failure.
A later 100 Hz conventional run aborted on excessive jitter; its failure is
retained. The final conventional/elevon runs explicitly use 50 Hz without weakening
the two-period jitter safeguard. Earlier startup DataFlash logs lacked calibration;
periodic configuration logging fixes reconstruction. Mixed defaults are merged to
avoid this fork's deferred DDS-parameter loading issue.

## Limits and checks not exercised

- This is development/SITL evidence, not physical-aircraft qualification. PWM is a
  commanded output, not measured surface position.
- Controller anti-windup does not directly observe the additional actuator clipping.
  Spectral plots describe closed-loop response; correlated multi-axis inputs need
  multivariable identification before attributing a transfer function to one axis.
- All QuadPlane configurations, servo auto-trim, active navigation scripting and
  unsupported mixers are conservatively excluded. One command publisher is assumed;
  sequence ordering is not authentication.
- Live DDS agent reconnection, a live AP-clock discontinuity, every failsafe combination,
  dedicated flaperon flight dynamics and hardware timing/load limits were not
  exercised. Core clock/disconnect fault and reactivation paths are unit-tested;
  this does not substitute for those live integration cases.
- Clean-machine container image construction remains unverified: Compose uses
  existing local ROS/agent images. Host-native ROS checks were unavailable and ran
  in Docker instead. The fork retains two existing 60-second DDS startup delays.
- The broad original verification matrix is therefore not fully closed. Only checks
  listed as executed above are claimed as passed.
