# bot_low_level
Low Level helpers to read sensors / control actuators via GPIO

* Sonar HCRS04 driver to read distance
* LN258N motor driver to control DC motors
* Incremental Optical Encoder driver to read wheel ticks
* PID velocity control with Lueneberger Observer / Sliding Average Filter for speed control of DC motors

Usage:

For Arduino place in ~/Arduino/libraries/..

Use as library in sketch file e.g.:

https://github.com/phildue/arduino_motor_control
