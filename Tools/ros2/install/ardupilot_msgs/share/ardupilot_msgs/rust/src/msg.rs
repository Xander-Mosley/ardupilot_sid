#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to ardupilot_msgs__msg__GlobalPosition
/// Experimental REP-147 Goal Interface
/// https://ros.org/reps/rep-0147.html#goal-interface

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GlobalPosition {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coordinate_frame: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub type_mask: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub latitude: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub longitude: f64,

    /// in meters, AMSL or above terrain
    pub altitude: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: geometry_msgs::msg::Twist,


    // This member is not documented.
    #[allow(missing_docs)]
    pub acceleration_or_force: geometry_msgs::msg::Twist,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f32,

}

impl GlobalPosition {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FRAME_GLOBAL_INT: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FRAME_GLOBAL_REL_ALT: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FRAME_GLOBAL_TERRAIN_ALT: u8 = 11;

    /// Position ignore flags
    pub const IGNORE_LATITUDE: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_LONGITUDE: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_ALTITUDE: u16 = 4;

    /// Velocity vector ignore flags
    pub const IGNORE_VX: u16 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_VY: u16 = 16;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_VZ: u16 = 32;

    /// Acceleration/Force vector ignore flags
    pub const IGNORE_AFX: u16 = 64;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_AFY: u16 = 128;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_AFZ: u16 = 256;

    /// Force in af vector flag
    pub const FORCE: u16 = 512;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_YAW: u16 = 1024;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const IGNORE_YAW_RATE: u16 = 2048;

}


impl Default for GlobalPosition {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GlobalPosition::default())
  }
}

impl rosidl_runtime_rs::Message for GlobalPosition {
  type RmwMsg = super::msg::rmw::GlobalPosition;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        coordinate_frame: msg.coordinate_frame,
        type_mask: msg.type_mask,
        latitude: msg.latitude,
        longitude: msg.longitude,
        altitude: msg.altitude,
        velocity: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Owned(msg.velocity)).into_owned(),
        acceleration_or_force: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Owned(msg.acceleration_or_force)).into_owned(),
        yaw: msg.yaw,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      coordinate_frame: msg.coordinate_frame,
      type_mask: msg.type_mask,
      latitude: msg.latitude,
      longitude: msg.longitude,
      altitude: msg.altitude,
        velocity: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Borrowed(&msg.velocity)).into_owned(),
        acceleration_or_force: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Borrowed(&msg.acceleration_or_force)).into_owned(),
      yaw: msg.yaw,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      coordinate_frame: msg.coordinate_frame,
      type_mask: msg.type_mask,
      latitude: msg.latitude,
      longitude: msg.longitude,
      altitude: msg.altitude,
      velocity: geometry_msgs::msg::Twist::from_rmw_message(msg.velocity),
      acceleration_or_force: geometry_msgs::msg::Twist::from_rmw_message(msg.acceleration_or_force),
      yaw: msg.yaw,
    }
  }
}


// Corresponds to ardupilot_msgs__msg__Pitot
/// Raw pitot tube / airspeed sensor data.
///
/// Units:
///   differential_pressure : Pa     (Measured pitot-static pressure difference, ΔP)
///   dynamic_pressure      : Pa     (q = 0.5 * ρ * V²)
///   calibrated_airspeed   : m/s    (CAS = sqrt(2q / ρ₀))
///   true_airspeed         : m/s    (TAS = CAS * sqrt(ρ₀ / ρ))
///   temperature           : °C     (Measured sensor or ambient air temperature)
///   air_density           : kg/m³  (Local atmospheric air density)
///
/// Notes:
/// - Values originate from AP_Airspeed and AP_Baro before EKF fusion.
/// - ρ₀ = 1.225 kg/m³ (ISA sea-level air density)
/// - ρ = local atmospheric air density
/// - q = dynamic pressure

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Pitot {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub differential_pressure: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dynamic_pressure: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub calibrated_airspeed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub true_airspeed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub temperature: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub air_density: f32,

}



impl Default for Pitot {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Pitot::default())
  }
}

impl rosidl_runtime_rs::Message for Pitot {
  type RmwMsg = super::msg::rmw::Pitot;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        differential_pressure: msg.differential_pressure,
        dynamic_pressure: msg.dynamic_pressure,
        calibrated_airspeed: msg.calibrated_airspeed,
        true_airspeed: msg.true_airspeed,
        temperature: msg.temperature,
        air_density: msg.air_density,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      differential_pressure: msg.differential_pressure,
      dynamic_pressure: msg.dynamic_pressure,
      calibrated_airspeed: msg.calibrated_airspeed,
      true_airspeed: msg.true_airspeed,
      temperature: msg.temperature,
      air_density: msg.air_density,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      differential_pressure: msg.differential_pressure,
      dynamic_pressure: msg.dynamic_pressure,
      calibrated_airspeed: msg.calibrated_airspeed,
      true_airspeed: msg.true_airspeed,
      temperature: msg.temperature,
      air_density: msg.air_density,
    }
  }
}


// Corresponds to ardupilot_msgs__msg__Propulsion
/// Propulsion system telemetry.
///
/// Units:
///   rpm         : revolutions/minute
///   voltage     : V
///   current     : A
///   temperature : °C
///
/// Notes:
/// - Values originate from ESC or propulsion telemetry, AP_ESC_Telem (when available).
/// - Electrical power may be computed as:
///     power = voltage × current (W)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Propulsion {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rpm: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub voltage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub temperature: f32,

}



impl Default for Propulsion {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Propulsion::default())
  }
}

impl rosidl_runtime_rs::Message for Propulsion {
  type RmwMsg = super::msg::rmw::Propulsion;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        rpm: msg.rpm,
        voltage: msg.voltage,
        current: msg.current,
        temperature: msg.temperature,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      rpm: msg.rpm,
      voltage: msg.voltage,
      current: msg.current,
      temperature: msg.temperature,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      rpm: msg.rpm,
      voltage: msg.voltage,
      current: msg.current,
      temperature: msg.temperature,
    }
  }
}


// Corresponds to ardupilot_msgs__msg__RcIn
/// PWM values received by the flight controller from the RC receiver.
///
/// Units:
///   values : µs (PWM pulse width)
///
/// Notes:
/// - RC input backend (AP_RCProtocol / RC_Channel).
/// - Bit i of valid_mask corresponds to values[i].
/// - A set bit indicates the corresponding PWM value is valid.
/// - Clear bits indicate the corresponding array element should be ignored.
/// - Example:
///     valid_mask = 0x000F
///     -> values[0]..values[3] are valid
///     -> values[4]..values[15] should be ignored

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RcIn {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub valid_mask: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub values: [u16; 16],

}



impl Default for RcIn {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RcIn::default())
  }
}

impl rosidl_runtime_rs::Message for RcIn {
  type RmwMsg = super::msg::rmw::RcIn;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        valid_mask: msg.valid_mask,
        values: msg.values,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      valid_mask: msg.valid_mask,
        values: msg.values,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      valid_mask: msg.valid_mask,
      values: msg.values,
    }
  }
}


// Corresponds to ardupilot_msgs__msg__RcOut
/// PWM values sent by the flight controller to the aircraft servos.
///
/// Units:
///   values : µs (PWM pulse width)
///
/// Notes:
/// - SRV_Channel output PWM values.
/// - Bit i of valid_mask corresponds to values[i].
/// - A set bit indicates the corresponding PWM value is valid.
/// - Clear bits indicate the corresponding array element should be ignored.
/// - Example:
///     valid_mask = 0x000F
///     -> values[0]..values[3] are valid
///     -> values[4]..values[15] should be ignored

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RcOut {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub valid_mask: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub values: [u16; 16],

}



impl Default for RcOut {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RcOut::default())
  }
}

impl rosidl_runtime_rs::Message for RcOut {
  type RmwMsg = super::msg::rmw::RcOut;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        valid_mask: msg.valid_mask,
        values: msg.values,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      valid_mask: msg.valid_mask,
        values: msg.values,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      valid_mask: msg.valid_mask,
      values: msg.values,
    }
  }
}


