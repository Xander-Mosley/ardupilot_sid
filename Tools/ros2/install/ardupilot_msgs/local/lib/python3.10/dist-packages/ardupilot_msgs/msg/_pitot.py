# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ardupilot_msgs:msg/Pitot.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Pitot(type):
    """Metaclass of message 'Pitot'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('ardupilot_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ardupilot_msgs.msg.Pitot')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pitot
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pitot
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pitot
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pitot
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pitot

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Pitot(metaclass=Metaclass_Pitot):
    """Message class 'Pitot'."""

    __slots__ = [
        '_header',
        '_differential_pressure',
        '_dynamic_pressure',
        '_calibrated_airspeed',
        '_true_airspeed',
        '_temperature',
        '_air_density',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'differential_pressure': 'float',
        'dynamic_pressure': 'float',
        'calibrated_airspeed': 'float',
        'true_airspeed': 'float',
        'temperature': 'float',
        'air_density': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.differential_pressure = kwargs.get('differential_pressure', float())
        self.dynamic_pressure = kwargs.get('dynamic_pressure', float())
        self.calibrated_airspeed = kwargs.get('calibrated_airspeed', float())
        self.true_airspeed = kwargs.get('true_airspeed', float())
        self.temperature = kwargs.get('temperature', float())
        self.air_density = kwargs.get('air_density', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.differential_pressure != other.differential_pressure:
            return False
        if self.dynamic_pressure != other.dynamic_pressure:
            return False
        if self.calibrated_airspeed != other.calibrated_airspeed:
            return False
        if self.true_airspeed != other.true_airspeed:
            return False
        if self.temperature != other.temperature:
            return False
        if self.air_density != other.air_density:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def differential_pressure(self):
        """Message field 'differential_pressure'."""
        return self._differential_pressure

    @differential_pressure.setter
    def differential_pressure(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'differential_pressure' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'differential_pressure' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._differential_pressure = value

    @builtins.property
    def dynamic_pressure(self):
        """Message field 'dynamic_pressure'."""
        return self._dynamic_pressure

    @dynamic_pressure.setter
    def dynamic_pressure(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'dynamic_pressure' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'dynamic_pressure' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._dynamic_pressure = value

    @builtins.property
    def calibrated_airspeed(self):
        """Message field 'calibrated_airspeed'."""
        return self._calibrated_airspeed

    @calibrated_airspeed.setter
    def calibrated_airspeed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'calibrated_airspeed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'calibrated_airspeed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._calibrated_airspeed = value

    @builtins.property
    def true_airspeed(self):
        """Message field 'true_airspeed'."""
        return self._true_airspeed

    @true_airspeed.setter
    def true_airspeed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'true_airspeed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'true_airspeed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._true_airspeed = value

    @builtins.property
    def temperature(self):
        """Message field 'temperature'."""
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'temperature' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'temperature' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._temperature = value

    @builtins.property
    def air_density(self):
        """Message field 'air_density'."""
        return self._air_density

    @air_density.setter
    def air_density(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'air_density' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'air_density' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._air_density = value
