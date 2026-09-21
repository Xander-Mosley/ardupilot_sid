// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ardupilot_msgs:msg/Propulsion.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__STRUCT_HPP_
#define ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ardupilot_msgs__msg__Propulsion __attribute__((deprecated))
#else
# define DEPRECATED__ardupilot_msgs__msg__Propulsion __declspec(deprecated)
#endif

namespace ardupilot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Propulsion_
{
  using Type = Propulsion_<ContainerAllocator>;

  explicit Propulsion_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rpm = 0.0f;
      this->voltage = 0.0f;
      this->current = 0.0f;
      this->temperature = 0.0f;
    }
  }

  explicit Propulsion_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rpm = 0.0f;
      this->voltage = 0.0f;
      this->current = 0.0f;
      this->temperature = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _rpm_type =
    float;
  _rpm_type rpm;
  using _voltage_type =
    float;
  _voltage_type voltage;
  using _current_type =
    float;
  _current_type current;
  using _temperature_type =
    float;
  _temperature_type temperature;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__rpm(
    const float & _arg)
  {
    this->rpm = _arg;
    return *this;
  }
  Type & set__voltage(
    const float & _arg)
  {
    this->voltage = _arg;
    return *this;
  }
  Type & set__current(
    const float & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__temperature(
    const float & _arg)
  {
    this->temperature = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ardupilot_msgs::msg::Propulsion_<ContainerAllocator> *;
  using ConstRawPtr =
    const ardupilot_msgs::msg::Propulsion_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ardupilot_msgs::msg::Propulsion_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ardupilot_msgs::msg::Propulsion_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ardupilot_msgs__msg__Propulsion
    std::shared_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ardupilot_msgs__msg__Propulsion
    std::shared_ptr<ardupilot_msgs::msg::Propulsion_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Propulsion_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->rpm != other.rpm) {
      return false;
    }
    if (this->voltage != other.voltage) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    return true;
  }
  bool operator!=(const Propulsion_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Propulsion_

// alias to use template instance with default allocator
using Propulsion =
  ardupilot_msgs::msg::Propulsion_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ardupilot_msgs

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PROPULSION__STRUCT_HPP_
