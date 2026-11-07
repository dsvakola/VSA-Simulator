"""
  Reading a Potentiometer
  Reads the voltage from a potentiometer and prints it in the Shell.

  On the ESP32 use an ADC1 pin (GPIO32 to GPIO39) for analog readings.
  ATTN_11DB lets the pin measure the whole 0 to 3.3 V range.
  read_u16() gives a number from 0 (0 V) to 65535 (full voltage). Turn the
  knob in VSA Simulator (click the potentiometer and drag the slider) and
  watch the numbers change in the Shell.

  The circuit:
  - Potentiometer outer legs -> 3V3 and GND
  - Potentiometer middle leg (wiper) -> D34 (GPIO34)

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 21 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 18 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, ADC
import time

pot = ADC(Pin(34))
pot.atten(ADC.ATTN_11DB)   # measure the full 0 to 3.3 V range

while True:
    value = pot.read_u16()             # 0 to 65535
    voltage = value * 3.3 / 65535     # turn it back into volts
    print("Value:", value, "  Voltage: {:.2f} V".format(voltage))
    time.sleep(0.5)   # print twice a second
