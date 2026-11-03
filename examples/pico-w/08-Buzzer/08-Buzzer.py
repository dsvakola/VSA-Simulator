"""
  Buzzer Beeps
  Beeps a buzzer three times, then pauses.

  An active buzzer makes its own sound: switch the pin to 1 and it beeps,
  switch it to 0 and it stops.

  The circuit:
  - Buzzer + (long leg) -> GP16
  - Buzzer - -> GND

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

buzzer = Pin(16, Pin.OUT)

def beep(ms):
    """One beep of the given length, then the same length of silence."""
    buzzer.value(1)
    time.sleep_ms(ms)
    buzzer.value(0)
    time.sleep_ms(ms)

while True:
    for i in range(3):   # three quick beeps...
        beep(150)
    time.sleep(1)        # ...then a pause
