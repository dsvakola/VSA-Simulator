"""
  Ultrasonic Distance Meter
  Measures distance with an HC-SR04 sensor and prints it.

  The program sends a 10 microsecond pulse on TRIG. The sensor sends out
  a burst of sound and holds ECHO high until the echo comes back.
  Sound travels about 0.034 cm per microsecond, there and back, so
  distance = time x 0.034 / 2.
  In VSA Simulator, click the sensor and move the distance slider.

  The HC-SR04 needs 5 V, so it takes its power from VIN. On a real board
  put a voltage divider (for example 1 k and 2 k) on the ECHO wire, so the
  pin never sees more than 3.3 V.

  The circuit:
  - HC-SR04 VCC -> VIN, GND -> GND
  - HC-SR04 TRIG -> D5 (GPIO14)
  - HC-SR04 ECHO -> D6 (GPIO12)

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 28 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 24 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, time_pulse_us
import time

trig = Pin(14, Pin.OUT, value=0)
echo = Pin(12, Pin.IN)

while True:
    trig.value(1)        # a 10 microsecond pulse starts a measurement
    time.sleep_us(10)
    trig.value(0)
    duration = time_pulse_us(echo, 1, 30000)   # how long ECHO stays high
    if duration < 0:
        print("No echo. Is the sensor connected?")
    else:
        distance = duration * 0.034 / 2
        print("Distance: {:.1f} cm".format(distance))
    time.sleep(0.5)
