"""
  OLED Bouncing Ball
  Shows a title and a bouncing ball on a 128x64 SSD1306 OLED.

  The OLED (address 0x3C) is driven with MicroPython's ssd1306 driver.
  Everything is drawn in memory first and appears when show() is called.

  You do not need to copy any library files; VSA Simulator adds them
  itself. On a real board, copy ssd1306.py onto the board with
  Thonny first.

  The circuit:
  - OLED GND -> GND, VCC -> 3V3
  - SDA -> D2 (GPIO4)
  - SCL -> D1 (GPIO5)

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 05 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 22 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, I2C
import ssd1306
import time

i2c = I2C(sda=Pin(4), scl=Pin(5))
oled = ssd1306.SSD1306_I2C(128, 64, i2c, addr=0x3C)

ball_x = 10   # where the ball is
step_x = 3    # how far it moves each time

while True:
    oled.fill(0)                          # clear the picture
    oled.text("VSA Simulator", 12, 8)     # 8x8 pixel letters
    oled.rect(0, 28, 128, 36, 1)          # a frame
    oled.ellipse(ball_x, 46, 6, 6, 1, True)   # the ball, filled
    oled.show()                           # nothing shows until this is called
    ball_x += step_x
    if ball_x < 8 or ball_x > 119:
        step_x = -step_x
        print("The ball bounced at x =", ball_x)   # print a message in the Shell
    time.sleep_ms(20)
