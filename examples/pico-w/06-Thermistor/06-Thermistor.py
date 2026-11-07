"""
  Thermistor Thermometer
  Measures the temperature with an NTC thermistor and prints it.

  An NTC thermistor's resistance falls as it gets warmer. With a 10 k
  resistor it makes a voltage divider; the program works out the
  thermistor's resistance from the voltage and turns it into degrees
  Celsius with the Beta formula.
  In VSA Simulator, click the thermistor and move the temperature slider.

  The Pico W reads 0 to 3.3 V on its ADC pins GP26, GP27 and GP28.

  The circuit:
  - Thermistor (10 k, Beta 3950): 3V3(OUT) -> thermistor -> GP26 (ADC0)
  - 10 k resistor: GP26 (ADC0) -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 25 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 23 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, ADC
import math
import time

sensor = ADC(26)
SUPPLY = 3.3              # the divider is powered from 3V3
SERIES_RESISTOR = 10000   # the fixed 10 k resistor
NOMINAL_R = 10000         # thermistor resistance at 25 C
NOMINAL_TEMP = 25.0       # that temperature, in C
BETA = 3950               # the thermistor's Beta value

while True:
    voltage = sensor.read_u16() * 3.3 / 65535
    if voltage < 0.01:
        voltage = 0.01    # avoid dividing by zero
    # The thermistor is at the top of the divider.
    resistance = SERIES_RESISTOR * (SUPPLY / voltage - 1)
    # Beta formula: 1/T = 1/T0 + (1/B) * ln(R/R0), with T in kelvin.
    kelvin = 1 / (1 / (NOMINAL_TEMP + 273.15) + math.log(resistance / NOMINAL_R) / BETA)
    celsius = kelvin - 273.15
    print("Temperature: {:.1f} C".format(celsius))
    time.sleep(1)
