// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ardupilot_msgs:msg/Propulsion.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__STRUCT_H_
#define ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__STRUCT_H_

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

/// Struct defined in msg/Propulsion in the package ardupilot_msgs.
/**
  * Propulsion system telemetry.
  *
  * Units:
  *   rpm         : revolutions/minute
  *   voltage     : V
  *   current     : A
  *   temperature : °C
  *
  * Notes:
  * - Values originate from ESC or propulsion telemetry, AP_ESC_Telem (when available).
  * - Electrical power may be computed as:
  *     power = voltage × current (W)
 */
typedef struct ardupilot_msgs__msg__Propulsion
{
  std_msgs__msg__Header header;
  float rpm;
  float voltage;
  float current;
  float temperature;
} ardupilot_msgs__msg__Propulsion;

// Struct for a sequence of ardupilot_msgs__msg__Propulsion.
typedef struct ardupilot_msgs__msg__Propulsion__Sequence
{
  ardupilot_msgs__msg__Propulsion * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ardupilot_msgs__msg__Propulsion__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__STRUCT_H_
