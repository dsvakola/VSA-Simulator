"""
  I2C LCD Display
  Shows a title and a running seconds counter on a 16x2 I2C LCD.

  The LCD has a small I2C board on its back (address 0x27), so it needs
  only 4 wires. It needs 5 V, so it takes its power from VBUS.

  You do not need to copy any library files; VSA Simulator adds them
  itself. On a real board, copy pico_i2c_lcd.py and lcd_api.py onto the board with
  Thonny first.

  The circuit:
  - LCD GND -> GND, VCC -> VBUS
  - SDA -> GP4
  - SCL -> GP5

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Modified 03 November 2026 by Prof. Dattaraj S. Vidyasagar
  Modified 04 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, I2C
from pico_i2c_lcd import I2cLcd
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5))
lcd = I2cLcd(i2c, 0x27, 2, 16)   # address, 2 lines, 16 columns

lcd.backlight_on()
lcd.move_to(0, 0)        # column 0, line 0 (the top line)
lcd.putstr("VSA Simulator")
lcd.move_to(0, 1)        # column 0, line 1 (the bottom line)
lcd.putstr("Seconds: ")
start = time.ticks_ms()

while True:
    seconds = time.ticks_diff(time.ticks_ms(), start) // 1000
    lcd.move_to(9, 1)    # just after "Seconds: "
    lcd.putstr(str(seconds))
    time.sleep_ms(200)
