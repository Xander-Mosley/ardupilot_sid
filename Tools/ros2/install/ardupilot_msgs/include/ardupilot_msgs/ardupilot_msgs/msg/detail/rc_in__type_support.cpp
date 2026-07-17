// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from ardupilot_msgs:msg/RcIn.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "ardupilot_msgs/msg/detail/rc_in__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace ardupilot_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void RcIn_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) ardupilot_msgs::msg::RcIn(_init);
}

void RcIn_fini_function(void * message_memory)
{
  auto typed_message = static_cast<ardupilot_msgs::msg::RcIn *>(message_memory);
  typed_message->~RcIn();
}

size_t size_function__RcIn__values(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__RcIn__values(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint16_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__RcIn__values(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint16_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__RcIn__values(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint16_t *>(
    get_const_function__RcIn__values(untyped_member, index));
  auto & value = *reinterpret_cast<uint16_t *>(untyped_value);
  value = item;
}

void assign_function__RcIn__values(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint16_t *>(
    get_function__RcIn__values(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint16_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RcIn_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ardupilot_msgs::msg::RcIn, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "valid_mask",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ardupilot_msgs::msg::RcIn, valid_mask),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "values",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(ardupilot_msgs::msg::RcIn, values),  // bytes offset in struct
    nullptr,  // default value
    size_function__RcIn__values,  // size() function pointer
    get_const_function__RcIn__values,  // get_const(index) function pointer
    get_function__RcIn__values,  // get(index) function pointer
    fetch_function__RcIn__values,  // fetch(index, &value) function pointer
    assign_function__RcIn__values,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RcIn_message_members = {
  "ardupilot_msgs::msg",  // message namespace
  "RcIn",  // message name
  3,  // number of fields
  sizeof(ardupilot_msgs::msg::RcIn),
  RcIn_message_member_array,  // message members
  RcIn_init_function,  // function to initialize message memory (memory has to be allocated)
  RcIn_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RcIn_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RcIn_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace ardupilot_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<ardupilot_msgs::msg::RcIn>()
{
  return &::ardupilot_msgs::msg::rosidl_typesupport_introspection_cpp::RcIn_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, ardupilot_msgs, msg, RcIn)() {
  return &::ardupilot_msgs::msg::rosidl_typesupport_introspection_cpp::RcIn_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
