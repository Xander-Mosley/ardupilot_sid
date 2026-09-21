# Propulsion system telemetry.
#
# Units:
#   rpm         : revolutions/minute
#   voltage     : V
#   current     : A
#   temperature : °C
#
# Notes:
# - Values originate from ESC or propulsion telemetry, AP_ESC_Telem (when available).
# - Electrical power may be computed as:
#     power = voltage × current (W)

std_msgs/Header header

float32 rpm

float32 voltage
float32 current

float32 temperature