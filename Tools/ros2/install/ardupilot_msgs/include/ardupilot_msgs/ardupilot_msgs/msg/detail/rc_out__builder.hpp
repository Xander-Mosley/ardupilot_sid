// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ardupilot_msgs:msg/RcOut.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__RC_OUT__BUILDER_HPP_
#define ARDUPILOT_MSGS__MSG__DETAIL__RC_OUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ardupilot_msgs/msg/detail/rc_out__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ardupilot_msgs
{

namespace msg
{

namespace builder
{

class Init_RcOut_values
{
public:
  explicit Init_RcOut_values(::ardupilot_msgs::msg::RcOut & msg)
  : msg_(msg)
  {}
  ::ardupilot_msgs::msg::RcOut values(::ardupilot_msgs::msg::RcOut::_values_type arg)
  {
    msg_.values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ardupilot_msgs::msg::RcOut msg_;
};

class Init_RcOut_valid_mask
{
public:
  explicit Init_RcOut_valid_mask(::ardupilot_msgs::msg::RcOut & msg)
  : msg_(msg)
  {}
  Init_RcOut_values valid_mask(::ardupilot_msgs::msg::RcOut::_valid_mask_type arg)
  {
    msg_.valid_mask = std::move(arg);
    return Init_RcOut_values(msg_);
  }

private:
  ::ardupilot_msgs::msg::RcOut msg_;
};

class Init_RcOut_header
{
public:
  Init_RcOut_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RcOut_valid_mask header(::ardupilot_msgs::msg::RcOut::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RcOut_valid_mask(msg_);
  }

private:
  ::ardupilot_msgs::msg::RcOut msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ardupilot_msgs::msg::RcOut>()
{
  return ardupilot_msgs::msg::builder::Init_RcOut_header();
}

}  // namespace ardupilot_msgs

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__RC_OUT__BUILDER_HPP_
