// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ardupilot_msgs:msg/Pitot.idl
// generated code does not contain a copyright notice

#ifndef ARDUPILOT_MSGS__MSG__DETAIL__PITOT__STRUCT_HPP_
#define ARDUPILOT_MSGS__MSG__DETAIL__PITOT__STRUCT_HPP_

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
# define DEPRECATED__ardupilot_msgs__msg__Pitot __attribute__((deprecated))
#else
# define DEPRECATED__ardupilot_msgs__msg__Pitot __declspec(deprecated)
#endif

namespace ardupilot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Pitot_
{
  using Type = Pitot_<ContainerAllocator>;

  explicit Pitot_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->differential_pressure = 0.0f;
      this->dynamic_pressure = 0.0f;
      this->calibrated_airspeed = 0.0f;
      this->true_airspeed = 0.0f;
      this->temperature = 0.0f;
      this->air_density = 0.0f;
    }
  }

  explicit Pitot_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->differential_pressure = 0.0f;
      this->dynamic_pressure = 0.0f;
      this->calibrated_airspeed = 0.0f;
      this->true_airspeed = 0.0f;
      this->temperature = 0.0f;
      this->air_density = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _differential_pressure_type =
    float;
  _differential_pressure_type differential_pressure;
  using _dynamic_pressure_type =
    float;
  _dynamic_pressure_type dynamic_pressure;
  using _calibrated_airspeed_type =
    float;
  _calibrated_airspeed_type calibrated_airspeed;
  using _true_airspeed_type =
    float;
  _true_airspeed_type true_airspeed;
  using _temperature_type =
    float;
  _temperature_type temperature;
  using _air_density_type =
    float;
  _air_density_type air_density;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__differential_pressure(
    const float & _arg)
  {
    this->differential_pressure = _arg;
    return *this;
  }
  Type & set__dynamic_pressure(
    const float & _arg)
  {
    this->dynamic_pressure = _arg;
    return *this;
  }
  Type & set__calibrated_airspeed(
    const float & _arg)
  {
    this->calibrated_airspeed = _arg;
    return *this;
  }
  Type & set__true_airspeed(
    const float & _arg)
  {
    this->true_airspeed = _arg;
    return *this;
  }
  Type & set__temperature(
    const float & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__air_density(
    const float & _arg)
  {
    this->air_density = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ardupilot_msgs::msg::Pitot_<ContainerAllocator> *;
  using ConstRawPtr =
    const ardupilot_msgs::msg::Pitot_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ardupilot_msgs::msg::Pitot_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ardupilot_msgs::msg::Pitot_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ardupilot_msgs__msg__Pitot
    std::shared_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ardupilot_msgs__msg__Pitot
    std::shared_ptr<ardupilot_msgs::msg::Pitot_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Pitot_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->differential_pressure != other.differential_pressure) {
      return false;
    }
    if (this->dynamic_pressure != other.dynamic_pressure) {
      return false;
    }
    if (this->calibrated_airspeed != other.calibrated_airspeed) {
      return false;
    }
    if (this->true_airspeed != other.true_airspeed) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->air_density != other.air_density) {
      return false;
    }
    return true;
  }
  bool operator!=(const Pitot_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Pitot_

// alias to use template instance with default allocator
using Pitot =
  ardupilot_msgs::msg::Pitot_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ardupilot_msgs

#endif  // ARDUPILOT_MSGS__MSG__DETAIL__PITOT__STRUCT_HPP_
