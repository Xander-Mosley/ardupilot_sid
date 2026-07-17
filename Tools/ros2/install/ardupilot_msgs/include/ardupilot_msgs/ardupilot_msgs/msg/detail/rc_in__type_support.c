// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ardupilot_msgs:msg/RcIn.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ardupilot_msgs/msg/detail/rc_in__rosidl_typesupport_introspection_c.h"
#include "ardupilot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ardupilot_msgs/msg/detail/rc_in__functions.h"
#include "ardupilot_msgs/msg/detail/rc_in__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ardupilot_msgs__msg__RcIn__init(message_memory);
}

void ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_fini_function(void * message_memory)
{
  ardupilot_msgs__msg__RcIn__fini(message_memory);
}

size_t ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__size_function__RcIn__values(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__get_const_function__RcIn__values(
  const void * untyped_member, size_t index)
{
  const uint16_t * member =
    (const uint16_t *)(untyped_member);
  return &member[index];
}

void * ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__get_function__RcIn__values(
  void * untyped_member, size_t index)
{
  uint16_t * member =
    (uint16_t *)(untyped_member);
  return &member[index];
}

void ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__fetch_function__RcIn__values(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint16_t * item =
    ((const uint16_t *)
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__get_const_function__RcIn__values(untyped_member, index));
  uint16_t * value =
    (uint16_t *)(untyped_value);
  *value = *item;
}

void ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__assign_function__RcIn__values(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint16_t * item =
    ((uint16_t *)
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__get_function__RcIn__values(untyped_member, index));
  const uint16_t * value =
    (const uint16_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ardupilot_msgs__msg__RcIn, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "valid_mask",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ardupilot_msgs__msg__RcIn, valid_mask),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "values",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(ardupilot_msgs__msg__RcIn, values),  // bytes offset in struct
    NULL,  // default value
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__size_function__RcIn__values,  // size() function pointer
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__get_const_function__RcIn__values,  // get_const(index) function pointer
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__get_function__RcIn__values,  // get(index) function pointer
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__fetch_function__RcIn__values,  // fetch(index, &value) function pointer
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__assign_function__RcIn__values,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_members = {
  "ardupilot_msgs__msg",  // message namespace
  "RcIn",  // message name
  3,  // number of fields
  sizeof(ardupilot_msgs__msg__RcIn),
  ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_member_array,  // message members
  ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_init_function,  // function to initialize message memory (memory has to be allocated)
  ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_type_support_handle = {
  0,
  &ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ardupilot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ardupilot_msgs, msg, RcIn)() {
  ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_type_support_handle.typesupport_identifier) {
    ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ardupilot_msgs__msg__RcIn__rosidl_typesupport_introspection_c__RcIn_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
