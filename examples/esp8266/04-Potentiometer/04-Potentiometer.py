"""
  Reading a Potentiometer
  Reads the voltage from a potentiometer and prints it in the Shell.

  The ESP8266 has only one analog pin, A0. On the NodeMCU board it reads
  0 to about 3.2 V.
  read_u16() gives a number from 0 (0 V) to 65535 (full voltage). Turn the
  knob in VSA Simulator (click the potentiometer and drag the slider) and
  watch the numbers change in the Shell.

  The circuit:
  - Potentiometer outer legs -> 3V3 and GND
  - Potentiometer middle leg (wiper) -> A0

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

from machine import Pin, ADC
import time

pot = ADC(0)

while True:
    value = pot.read_u16()             # 0 to 65535
    voltage = value * 3.2 / 65535     # turn it back into volts
    print("Value:", value, "  Voltage: {:.2f} V".format(voltage))
    time.sleep(0.5)   # print twice a second
