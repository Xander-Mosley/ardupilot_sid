# PWM values received by the flight controller from the RC receiver.
#
# Units:
#   values : µs (PWM pulse width)
#
# Notes:
# - RC input backend (AP_RCProtocol / RC_Channel).
# - Bit i of valid_mask corresponds to values[i].
# - A set bit indicates the corresponding PWM value is valid.
# - Clear bits indicate the corresponding array element should be ignored.
# - Example:
#     valid_mask = 0x000F
#     -> values[0]..values[3] are valid
#     -> values[4]..values[15] should be ignored

std_msgs/Header header

uint16 valid_mask
uint16[16] values