"""
  LDR Night Light
  Switches an LED on when it gets dark.

  The LDR (light dependent resistor) and a 10 k resistor make a voltage
  divider. In bright light the LDR's resistance is low and the voltage on
  the analog pin is high. In the dark it is low.
  In VSA Simulator, click the LDR and move the light slider.

  On the ESP32 use an ADC1 pin (GPIO32 to GPIO39) for analog readings.
  ATTN_11DB lets the pin measure the whole 0 to 3.3 V range.

  The circuit:
  - LDR: 3V3 -> LDR -> D34 (GPIO34)
  - 10 k resistor: D34 (GPIO34) -> GND
  - LED: D13 (GPIO13) -> 220 ohm resistor -> LED anode, LED cathode -> GND

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 25 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 29 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, ADC
import time

ldr = ADC(Pin(34))
ldr.atten(ADC.ATTN_11DB)   # measure the full 0 to 3.3 V range
led = Pin(13, Pin.OUT)
DARK_LEVEL = 20000   # below this reading we call it "dark"

while True:
    light = ldr.read_u16()   # high = bright, low = dark
    print("Light level:", light)
    if light < DARK_LEVEL:
        led.value(1)   # dark: switch the light on
    else:
        led.value(0)   # bright: switch it off
    time.sleep(0.3)
