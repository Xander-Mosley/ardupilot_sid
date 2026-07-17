// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from ardupilot_msgs:msg/Pitot.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "ardupilot_msgs/msg/detail/pitot__struct.h"
#include "ardupilot_msgs/msg/detail/pitot__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool ardupilot_msgs__msg__pitot__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[32];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("ardupilot_msgs.msg._pitot.Pitot", full_classname_dest, 31) == 0);
  }
  ardupilot_msgs__msg__Pitot * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // differential_pressure
    PyObject * field = PyObject_GetAttrString(_pymsg, "differential_pressure");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->differential_pressure = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // dynamic_pressure
    PyObject * field = PyObject_GetAttrString(_pymsg, "dynamic_pressure");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->dynamic_pressure = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // calibrated_airspeed
    PyObject * field = PyObject_GetAttrString(_pymsg, "calibrated_airspeed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->calibrated_airspeed = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // true_airspeed
    PyObject * field = PyObject_GetAttrString(_pymsg, "true_airspeed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->true_airspeed = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // temperature
    PyObject * field = PyObject_GetAttrString(_pymsg, "temperature");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->temperature = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // air_density
    PyObject * field = PyObject_GetAttrString(_pymsg, "air_density");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->air_density = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * ardupilot_msgs__msg__pitot__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Pitot */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("ardupilot_msgs.msg._pitot");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Pitot");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  ardupilot_msgs__msg__Pitot * ros_message = (ardupilot_msgs__msg__Pitot *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // differential_pressure
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->differential_pressure);
    {
      int rc = PyObject_SetAttrString(_pymessage, "differential_pressure", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dynamic_pressure
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->dynamic_pressure);
    {
      int rc = PyObject_SetAttrString(_pymessage, "dynamic_pressure", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // calibrated_airspeed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->calibrated_airspeed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "calibrated_airspeed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // true_airspeed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->true_airspeed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "true_airspeed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // temperature
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->temperature);
    {
      int rc = PyObject_SetAttrString(_pymessage, "temperature", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // air_density
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->air_density);
    {
      int rc = PyObject_SetAttrString(_pymessage, "air_density", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
