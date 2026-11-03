"""
  Blinking LED Code
  Turns the built-in LED on the ESP32 DevKit on and off.

  Most ESP32 DevKit boards have a blue on-board LED on GPIO2.
  This program blinks the built-in LED once every second. An external LED
  blinks together with it.

  To run it on a real board, open it in Thonny and press Run, or save it
  on the board as main.py so it starts by itself.

  The circuit:
  - External LED: D13 (GPIO13) -> 220 ohm resistor -> LED anode (long leg)
  - LED cathode (short leg) -> GND

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

from machine import Pin
import time

led = Pin(2, Pin.OUT)   # the on-board LED
led_ext = Pin(13, Pin.OUT)   # the external LED

while True:
    led.value(1)        # on-board LED on
    led_ext.value(1)    # external LED on
    time.sleep(1)       # wait for one second
    led.value(0)        # both off
    led_ext.value(0)
    time.sleep(1)       # wait for one second again
