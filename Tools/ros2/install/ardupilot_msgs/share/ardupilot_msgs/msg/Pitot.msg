# Raw pitot tube / airspeed sensor data.
#
# Units:
#   differential_pressure : Pa     (Measured pitot-static pressure difference, ΔP)
#   dynamic_pressure      : Pa     (q = 0.5 * ρ * V²)
#   calibrated_airspeed   : m/s    (CAS = sqrt(2q / ρ₀))
#   true_airspeed         : m/s    (TAS = CAS * sqrt(ρ₀ / ρ))
#   temperature           : °C     (Measured sensor or ambient air temperature)
#   air_density           : kg/m³  (Local atmospheric air density)
#
# Notes:
# - Values originate from AP_Airspeed before EKF fusion.
# - ρ₀ = 1.225 kg/m³ (ISA sea-level air density)
# - ρ = local atmospheric air density
# - q = dynamic pressure

std_msgs/Header header

float32 differential_pressure
float32 dynamic_pressure

float32 calibrated_airspeed
float32 true_airspeed

float32 temperature
float32 air_density