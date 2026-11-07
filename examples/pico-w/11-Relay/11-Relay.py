"""
  Relay Switch
  Switches a relay module on and off every two seconds.

  A relay is a switch worked by an electromagnet, so a small pin can
  switch a big load such as a lamp. The relay module needs 5 V, so it takes
  its power from the VBUS pin; its IN pin works with the board's 3.3 V
  signal.

  The circuit:
  - Relay module VCC -> VBUS
  - Relay module GND -> GND
  - Relay module IN -> GP15

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 01 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 21 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin
import time

relay = Pin(15, Pin.OUT)

while True:
    relay.value(1)   # relay on
    print("Relay ON")
    time.sleep(2)
    relay.value(0)   # relay off
    print("Relay OFF")
    time.sleep(2)
