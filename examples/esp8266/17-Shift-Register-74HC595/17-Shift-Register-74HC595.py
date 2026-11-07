"""
  74HC595 LED Chaser
  Drives 8 LEDs from 3 pins with a 74HC595 shift register.

  The program sends 8 bits, one at a time, on DS. Each pulse on SHCP
  moves them one place along. A pulse on STCP then shows all 8 at once on
  outputs Q0 to Q7. One lit LED runs from one end to the other and back.

  The 74HC595 runs from 3V3 here, so its outputs match the board's 3.3 V
  pins.

  The circuit:
  - 74HC595 DS (pin 14) -> D7 (GPIO13)
  - 74HC595 SHCP (pin 11) -> D5 (GPIO14)
  - 74HC595 STCP (pin 12) -> D6 (GPIO12)
  - VCC and MR -> 3V3; GND and OE -> GND
  - Q0 to Q7 -> 220 ohm resistor -> LED -> GND (8 times)

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 07 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 20 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin
import time

data = Pin(13, Pin.OUT)    # DS
clock = Pin(14, Pin.OUT)   # SHCP
latch = Pin(12, Pin.OUT)   # STCP

def write_leds(pattern):
    """Sends 8 bits (Q7 first) and then shows them on the outputs."""
    for bit in range(7, -1, -1):
        data.value((pattern >> bit) & 1)
        clock.value(1)   # move every bit one place along
        clock.value(0)
    latch.value(1)       # show all 8 bits at once
    latch.value(0)

while True:
    for i in range(8):          # from Q0 to Q7...
        write_leds(1 << i)
        print("LED Q" + str(i) + " is on")   # print which LED is on in the Shell
        time.sleep_ms(200)
    for i in range(6, 0, -1):   # ...and back again
        write_leds(1 << i)
        print("LED Q" + str(i) + " is on")   # print which LED is on in the Shell
        time.sleep_ms(200)
