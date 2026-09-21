// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ardupilot_msgs:msg/Pitot.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PITOT__STRUCT_H_
#define ARDUPILOT_MSGS__MSG__DETAIL__PITOT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/Pitot in the package ardupilot_msgs.
/**
  * Raw pitot tube / airspeed sensor data.
  *
  * Units:
  *   differential_pressure : Pa     (Measured pitot-static pressure difference, ΔP)
  *   dynamic_pressure      : Pa     (q = 0.5 * ρ * V²)
  *   calibrated_airspeed   : m/s    (CAS = sqrt(2q / ρ₀))
  *   true_airspeed         : m/s    (TAS = CAS * sqrt(ρ₀ / ρ))
  *   temperature           : °C     (Measured sensor or ambient air temperature)
  *   air_density           : kg/m³  (Local atmospheric air density)
  *
  * Notes:
  * - Values originate from AP_Airspeed and AP_Baro before EKF fusion.
  * - ρ₀ = 1.225 kg/m³ (ISA sea-level air density)
  * - ρ = local atmospheric air density
  * - q = dynamic pressure
 */
typedef struct ardupilot_msgs__msg__Pitot
{
  std_msgs__msg__Header header;
  float differential_pressure;
  float dynamic_pressure;
  float calibrated_airspeed;
  float true_airspeed;
  float temperature;
  float air_density;
} ardupilot_msgs__msg__Pitot;

// Struct for a sequence of ardupilot_msgs__msg__Pitot.
typedef struct ardupilot_msgs__msg__Pitot__Sequence
{
  ardupilot_msgs__msg__Pitot * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ardupilot_msgs__msg__Pitot__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PITOT__STRUCT_H_
