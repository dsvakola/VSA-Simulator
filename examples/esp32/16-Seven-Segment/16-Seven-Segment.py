"""
  Seven-Segment Counter
  Counts from 0 to 9 on a common-cathode seven-segment display (FND500).

  Each segment is an LED. A segment lights when its pin is 1. The common
  pin goes to GND through one 330 ohm resistor, so the display can run
  straight from the board's 3.3 V pins.

  The circuit:
  - Segment a: D13 (GPIO13)
  - Segment b: D12 (GPIO12)
  - Segment c: D14 (GPIO14)
  - Segment d: D27 (GPIO27)
  - Segment e: D26 (GPIO26)
  - Segment f: D25 (GPIO25)
  - Segment g: D33 (GPIO33)
  - Decimal point: D32 (GPIO32)
  - Common cathode -> 330 ohm resistor -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 04 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 26 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin
import time

# The pins for segments a, b, c, d, e, f and g.
segments = [Pin(n, Pin.OUT) for n in [13, 12, 14, 27, 26, 25, 33]]
dp = Pin(32, Pin.OUT)   # the decimal point

# Which segments (a to g) are lit for each digit: 1 = on.
DIGITS = [
    (1, 1, 1, 1, 1, 1, 0),   # 0
    (0, 1, 1, 0, 0, 0, 0),   # 1
    (1, 1, 0, 1, 1, 0, 1),   # 2
    (1, 1, 1, 1, 0, 0, 1),   # 3
    (0, 1, 1, 0, 0, 1, 1),   # 4
    (1, 0, 1, 1, 0, 1, 1),   # 5
    (1, 0, 1, 1, 1, 1, 1),   # 6
    (1, 1, 1, 0, 0, 0, 0),   # 7
    (1, 1, 1, 1, 1, 1, 1),   # 8
    (1, 1, 1, 1, 0, 1, 1),   # 9
]

def show_digit(n):
    for pin, lit in zip(segments, DIGITS[n]):
        pin.value(lit)

while True:
    for n in range(10):
        show_digit(n)
        print("Digit:", n)   # print the digit in the Shell
        dp.value(n % 2)   # the dot blinks with every count
        time.sleep(1)
