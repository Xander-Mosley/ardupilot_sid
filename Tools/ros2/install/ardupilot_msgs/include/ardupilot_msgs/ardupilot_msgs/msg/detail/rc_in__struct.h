// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ardupilot_msgs:msg/RcIn.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__RC_IN__STRUCT_H_
#define ARDUPILOT_MSGS__MSG__DETAIL__RC_IN__STRUCT_H_

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

/// Struct defined in msg/RcIn in the package ardupilot_msgs.
/**
  * PWM values received by the flight controller from the RC receiver.
  *
  * Units:
  *   values : µs (PWM pulse width)
  *
  * Notes:
  * - RC input backend (AP_RCProtocol / RC_Channel).
  * - Bit i of valid_mask corresponds to values[i].
  * - A set bit indicates the corresponding PWM value is valid.
  * - Clear bits indicate the corresponding array element should be ignored.
  * - Example:
  *     valid_mask = 0x000F
  *     -> values[0]..values[3] are valid
  *     -> values[4]..values[15] should be ignored
 */
typedef struct ardupilot_msgs__msg__RcIn
{
  std_msgs__msg__Header header;
  uint16_t valid_mask;
  uint16_t values[16];
} ardupilot_msgs__msg__RcIn;

// Struct for a sequence of ardupilot_msgs__msg__RcIn.
typedef struct ardupilot_msgs__msg__RcIn__Sequence
{
  ardupilot_msgs__msg__RcIn * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ardupilot_msgs__msg__RcIn__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__RC_IN__STRUCT_H_
