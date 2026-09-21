// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ardupilot_msgs:msg/Pitot.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PITOT__TRAITS_HPP_
#define ARDUPILOT_MSGS__MSG__DETAIL__PITOT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ardupilot_msgs/msg/detail/pitot__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace ardupilot_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Pitot & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: differential_pressure
  {
    out << "differential_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.differential_pressure, out);
    out << ", ";
  }

  // member: dynamic_pressure
  {
    out << "dynamic_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.dynamic_pressure, out);
    out << ", ";
  }

  // member: calibrated_airspeed
  {
    out << "calibrated_airspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.calibrated_airspeed, out);
    out << ", ";
  }

  // member: true_airspeed
  {
    out << "true_airspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.true_airspeed, out);
    out << ", ";
  }

  // member: temperature
  {
    out << "temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.temperature, out);
    out << ", ";
  }

  // member: air_density
  {
    out << "air_density: ";
    rosidl_generator_traits::value_to_yaml(msg.air_density, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Pitot & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: differential_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "differential_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.differential_pressure, out);
    out << "\n";
  }

  // member: dynamic_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dynamic_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.dynamic_pressure, out);
    out << "\n";
  }

  // member: calibrated_airspeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calibrated_airspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.calibrated_airspeed, out);
    out << "\n";
  }

  // member: true_airspeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "true_airspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.true_airspeed, out);
    out << "\n";
  }

  // member: temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.temperature, out);
    out << "\n";
  }

  // member: air_density
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "air_density: ";
    rosidl_generator_traits::value_to_yaml(msg.air_density, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Pitot & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace ardupilot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use ardupilot_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ardupilot_msgs::msg::Pitot & msg,
  std::ostream & out, size_t indentation = 0)
{
  ardupilot_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ardupilot_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const ardupilot_msgs::msg::Pitot & msg)
{
  return ardupilot_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<ardupilot_msgs::msg::Pitot>()
{
  return "ardupilot_msgs::msg::Pitot";
}

template<>
inline const char * name<ardupilot_msgs::msg::Pitot>()
{
  return "ardupilot_msgs/msg/Pitot";
}

template<>
struct has_fixed_size<ardupilot_msgs::msg::Pitot>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<ardupilot_msgs::msg::Pitot>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<ardupilot_msgs::msg::Pitot>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PITOT__TRAITS_HPP_
