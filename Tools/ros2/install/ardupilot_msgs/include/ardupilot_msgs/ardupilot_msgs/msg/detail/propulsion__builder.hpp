// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ardupilot_msgs:msg/Propulsion.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__BUILDER_HPP_
#define ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ardupilot_msgs/msg/detail/propulsion__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ardupilot_msgs
{

namespace msg
{

namespace builder
{

class Init_Propulsion_temperature
{
public:
  explicit Init_Propulsion_temperature(::ardupilot_msgs::msg::Propulsion & msg)
  : msg_(msg)
  {}
  ::ardupilot_msgs::msg::Propulsion temperature(::ardupilot_msgs::msg::Propulsion::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ardupilot_msgs::msg::Propulsion msg_;
};

class Init_Propulsion_current
{
public:
  explicit Init_Propulsion_current(::ardupilot_msgs::msg::Propulsion & msg)
  : msg_(msg)
  {}
  Init_Propulsion_temperature current(::ardupilot_msgs::msg::Propulsion::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_Propulsion_temperature(msg_);
  }

private:
  ::ardupilot_msgs::msg::Propulsion msg_;
};

class Init_Propulsion_voltage
{
public:
  explicit Init_Propulsion_voltage(::ardupilot_msgs::msg::Propulsion & msg)
  : msg_(msg)
  {}
  Init_Propulsion_current voltage(::ardupilot_msgs::msg::Propulsion::_voltage_type arg)
  {
    msg_.voltage = std::move(arg);
    return Init_Propulsion_current(msg_);
  }

private:
  ::ardupilot_msgs::msg::Propulsion msg_;
};

class Init_Propulsion_rpm
{
public:
  explicit Init_Propulsion_rpm(::ardupilot_msgs::msg::Propulsion & msg)
  : msg_(msg)
  {}
  Init_Propulsion_voltage rpm(::ardupilot_msgs::msg::Propulsion::_rpm_type arg)
  {
    msg_.rpm = std::move(arg);
    return Init_Propulsion_voltage(msg_);
  }

private:
  ::ardupilot_msgs::msg::Propulsion msg_;
};

class Init_Propulsion_header
{
public:
  Init_Propulsion_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Propulsion_rpm header(::ardupilot_msgs::msg::Propulsion::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Propulsion_rpm(msg_);
  }

private:
  ::ardupilot_msgs::msg::Propulsion msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ardupilot_msgs::msg::Propulsion>()
{
  return ardupilot_msgs::msg::builder::Init_Propulsion_header();
}

}  // namespace ardupilot_msgs

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__BUILDER_HPP_
