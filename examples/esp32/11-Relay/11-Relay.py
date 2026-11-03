"""
  Relay Switch
  Switches a relay module on and off every two seconds.

  A relay is a switch worked by an electromagnet, so a small pin can
  switch a big load such as a lamp. The relay module needs 5 V, so it takes
  its power from the VIN pin; its IN pin works with the board's 3.3 V
  signal.

  The circuit:
  - Relay module VCC -> VIN
  - Relay module GND -> GND
  - Relay module IN -> D13 (GPIO13)

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

relay = Pin(13, Pin.OUT)

while True:
    relay.value(1)   # relay on
    print("Relay ON")
    time.sleep(2)
    relay.value(0)   # relay off
    print("Relay OFF")
    time.sleep(2)
