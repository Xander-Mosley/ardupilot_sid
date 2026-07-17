// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ardupilot_msgs:msg/Pitot.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PITOT__BUILDER_HPP_
#define ARDUPILOT_MSGS__MSG__DETAIL__PITOT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ardupilot_msgs/msg/detail/pitot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ardupilot_msgs
{

namespace msg
{

namespace builder
{

class Init_Pitot_air_density
{
public:
  explicit Init_Pitot_air_density(::ardupilot_msgs::msg::Pitot & msg)
  : msg_(msg)
  {}
  ::ardupilot_msgs::msg::Pitot air_density(::ardupilot_msgs::msg::Pitot::_air_density_type arg)
  {
    msg_.air_density = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

class Init_Pitot_temperature
{
public:
  explicit Init_Pitot_temperature(::ardupilot_msgs::msg::Pitot & msg)
  : msg_(msg)
  {}
  Init_Pitot_air_density temperature(::ardupilot_msgs::msg::Pitot::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_Pitot_air_density(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

class Init_Pitot_true_airspeed
{
public:
  explicit Init_Pitot_true_airspeed(::ardupilot_msgs::msg::Pitot & msg)
  : msg_(msg)
  {}
  Init_Pitot_temperature true_airspeed(::ardupilot_msgs::msg::Pitot::_true_airspeed_type arg)
  {
    msg_.true_airspeed = std::move(arg);
    return Init_Pitot_temperature(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

class Init_Pitot_calibrated_airspeed
{
public:
  explicit Init_Pitot_calibrated_airspeed(::ardupilot_msgs::msg::Pitot & msg)
  : msg_(msg)
  {}
  Init_Pitot_true_airspeed calibrated_airspeed(::ardupilot_msgs::msg::Pitot::_calibrated_airspeed_type arg)
  {
    msg_.calibrated_airspeed = std::move(arg);
    return Init_Pitot_true_airspeed(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

class Init_Pitot_dynamic_pressure
{
public:
  explicit Init_Pitot_dynamic_pressure(::ardupilot_msgs::msg::Pitot & msg)
  : msg_(msg)
  {}
  Init_Pitot_calibrated_airspeed dynamic_pressure(::ardupilot_msgs::msg::Pitot::_dynamic_pressure_type arg)
  {
    msg_.dynamic_pressure = std::move(arg);
    return Init_Pitot_calibrated_airspeed(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

class Init_Pitot_differential_pressure
{
public:
  explicit Init_Pitot_differential_pressure(::ardupilot_msgs::msg::Pitot & msg)
  : msg_(msg)
  {}
  Init_Pitot_dynamic_pressure differential_pressure(::ardupilot_msgs::msg::Pitot::_differential_pressure_type arg)
  {
    msg_.differential_pressure = std::move(arg);
    return Init_Pitot_dynamic_pressure(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

class Init_Pitot_header
{
public:
  Init_Pitot_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pitot_differential_pressure header(::ardupilot_msgs::msg::Pitot::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Pitot_differential_pressure(msg_);
  }

private:
  ::ardupilot_msgs::msg::Pitot msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ardupilot_msgs::msg::Pitot>()
{
  return ardupilot_msgs::msg::builder::Init_Pitot_header();
}

}  // namespace ardupilot_msgs

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PITOT__BUILDER_HPP_
