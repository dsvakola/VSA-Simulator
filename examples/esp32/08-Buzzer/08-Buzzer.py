"""
  Buzzer Beeps
  Beeps a buzzer three times, then pauses.

  An active buzzer makes its own sound: switch the pin to 1 and it beeps,
  switch it to 0 and it stops.

  The circuit:
  - Buzzer + (long leg) -> D18 (GPIO18)
  - Buzzer - -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 15 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 20 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin
import time

buzzer = Pin(18, Pin.OUT)

def beep(ms):
    """One beep of the given length, then the same length of silence."""
    print("Beep for", ms, "ms")   # print a message in the Shell
    buzzer.value(1)
    time.sleep_ms(ms)
    buzzer.value(0)
    time.sleep_ms(ms)

while True:
    for i in range(3):   # three quick beeps...
        beep(150)
    print("Pause")
    time.sleep(1)        # ...then a pause
