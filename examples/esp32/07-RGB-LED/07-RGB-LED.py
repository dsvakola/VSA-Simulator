"""
  RGB LED Colours
  Mixes red, green and blue light to make different colours.

  An RGB LED is three LEDs (red, green and blue) in one case with a
  common cathode. Each colour gets its own PWM pin, so each can have any
  brightness from 0 to 65535. Mixing them makes other colours.

  The circuit:
  - Red: D25 (GPIO25) -> 220 ohm resistor -> R leg
  - Green: D26 (GPIO26) -> 220 ohm resistor -> G leg
  - Blue: D27 (GPIO27) -> 220 ohm resistor -> B leg
  - Common cathode (longest leg) -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 24 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 23 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, PWM
import time

red = PWM(Pin(25))
green = PWM(Pin(26))
blue = PWM(Pin(27))
for colour in (red, green, blue):
    colour.freq(1000)

def set_colour(r, g, b):
    """Each value goes from 0 (off) to 255 (full)."""
    red.duty_u16(r * 257)     # 255 * 257 = 65535
    green.duty_u16(g * 257)
    blue.duty_u16(b * 257)

while True:
    print("Colour: red")
    set_colour(255, 0, 0);     time.sleep(1)   # red
    print("Colour: green")
    set_colour(0, 255, 0);     time.sleep(1)   # green
    print("Colour: blue")
    set_colour(0, 0, 255);     time.sleep(1)   # blue
    print("Colour: yellow")
    set_colour(255, 255, 0);   time.sleep(1)   # yellow
    print("Colour: cyan")
    set_colour(0, 255, 255);   time.sleep(1)   # cyan
    print("Colour: magenta")
    set_colour(255, 0, 255);   time.sleep(1)   # magenta
    print("Colour: white")
    set_colour(255, 255, 255); time.sleep(1)   # white