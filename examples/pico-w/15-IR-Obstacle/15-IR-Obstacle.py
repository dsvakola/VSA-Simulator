"""
  IR Obstacle Sensor
  Lights an LED when the infrared sensor sees an obstacle.

  The IR obstacle sensor's OUT pin goes LOW (0) when something is close
  in front of it.
  In VSA Simulator, click the sensor and move the distance slider.

  The circuit:
  - IR sensor VCC -> 3V3(OUT), GND -> GND
  - IR sensor OUT -> GP14
  - LED: GP15 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 16 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 22 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin

sensor = Pin(14, Pin.IN)
led = Pin(15, Pin.OUT)
last_state = 1

while True:
    clear = sensor.value()   # 0 = object found
    if clear == 0:
        led.value(1)
    else:
        led.value(0)
    if clear != last_state:
        print("Obstacle ahead!" if clear == 0 else "The way is clear.")
        last_state = clear
