"""
  Fading LED
  Makes an LED slowly brighten and dim using PWM.

  PWM switches the pin on and off very fast. The longer it stays on in
  each cycle, the brighter the LED looks. duty_u16() takes a value from 0
  (always off) to 65535 (always on).

  The circuit:
  - D13 (GPIO13) -> 220 ohm resistor -> LED anode (long leg)
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

from machine import Pin, PWM
import time

led = PWM(Pin(13))
led.freq(1000)          # 1000 on/off cycles every second

while True:
    # Brighten: from off to full brightness in small steps.
    for duty in range(0, 65536, 1285):
        led.duty_u16(duty)
        time.sleep_ms(30)
    # Dim: back down to off.
    for duty in range(65535, -1, -1285):
        led.duty_u16(duty)
        time.sleep_ms(30)
