# Acquisition boot timestamp and matching /ap/time clock (microseconds).
# source: 0=AHRS estimate, 1=simulation truth. Angles radians, velocity FRD m/s.
# flags: velocity=1, finite=2, speed>=2=4, forward=8, healthy=16. Valid=31.
# Invalid angles are NaN; receipt time is not acquisition time.
uint64 time_us
uint64 clock_us
uint32 sequence_id
uint16 flags
uint16 rate_hz
uint8 source
float32 alpha
float32 beta
float32 u
float32 v
float32 w
