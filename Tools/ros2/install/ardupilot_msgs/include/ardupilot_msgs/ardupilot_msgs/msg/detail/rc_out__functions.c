// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ardupilot_msgs:msg/RcOut.idl
// generated code does not contain a copyright notice
#include "ardupilot_msgs/msg/detail/rc_out__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
ardupilot_msgs__msg__RcOut__init(ardupilot_msgs__msg__RcOut * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    ardupilot_msgs__msg__RcOut__fini(msg);
    return false;
  }
  // valid_mask
  // values
  return true;
}

void
ardupilot_msgs__msg__RcOut__fini(ardupilot_msgs__msg__RcOut * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // valid_mask
  // values
}

bool
ardupilot_msgs__msg__RcOut__are_equal(const ardupilot_msgs__msg__RcOut * lhs, const ardupilot_msgs__msg__RcOut * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // valid_mask
  if (lhs->valid_mask != rhs->valid_mask) {
    return false;
  }
  // values
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->values[i] != rhs->values[i]) {
      return false;
    }
  }
  return true;
}

bool
ardupilot_msgs__msg__RcOut__copy(
  const ardupilot_msgs__msg__RcOut * input,
  ardupilot_msgs__msg__RcOut * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // valid_mask
  output->valid_mask = input->valid_mask;
  // values
  for (size_t i = 0; i < 16; ++i) {
    output->values[i] = input->values[i];
  }
  return true;
}

ardupilot_msgs__msg__RcOut *
ardupilot_msgs__msg__RcOut__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ardupilot_msgs__msg__RcOut * msg = (ardupilot_msgs__msg__RcOut *)allocator.allocate(sizeof(ardupilot_msgs__msg__RcOut), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ardupilot_msgs__msg__RcOut));
  bool success = ardupilot_msgs__msg__RcOut__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ardupilot_msgs__msg__RcOut__destroy(ardupilot_msgs__msg__RcOut * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ardupilot_msgs__msg__RcOut__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ardupilot_msgs__msg__RcOut__Sequence__init(ardupilot_msgs__msg__RcOut__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ardupilot_msgs__msg__RcOut * data = NULL;

  if (size) {
    data = (ardupilot_msgs__msg__RcOut *)allocator.zero_allocate(size, sizeof(ardupilot_msgs__msg__RcOut), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ardupilot_msgs__msg__RcOut__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ardupilot_msgs__msg__RcOut__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ardupilot_msgs__msg__RcOut__Sequence__fini(ardupilot_msgs__msg__RcOut__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ardupilot_msgs__msg__RcOut__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ardupilot_msgs__msg__RcOut__Sequence *
ardupilot_msgs__msg__RcOut__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ardupilot_msgs__msg__RcOut__Sequence * array = (ardupilot_msgs__msg__RcOut__Sequence *)allocator.allocate(sizeof(ardupilot_msgs__msg__RcOut__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ardupilot_msgs__msg__RcOut__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ardupilot_msgs__msg__RcOut__Sequence__destroy(ardupilot_msgs__msg__RcOut__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ardupilot_msgs__msg__RcOut__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ardupilot_msgs__msg__RcOut__Sequence__are_equal(const ardupilot_msgs__msg__RcOut__Sequence * lhs, const ardupilot_msgs__msg__RcOut__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ardupilot_msgs__msg__RcOut__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ardupilot_msgs__msg__RcOut__Sequence__copy(
  const ardupilot_msgs__msg__RcOut__Sequence * input,
  ardupilot_msgs__msg__RcOut__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ardupilot_msgs__msg__RcOut);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ardupilot_msgs__msg__RcOut * data =
      (ardupilot_msgs__msg__RcOut *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ardupilot_msgs__msg__RcOut__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ardupilot_msgs__msg__RcOut__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ardupilot_msgs__msg__RcOut__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
