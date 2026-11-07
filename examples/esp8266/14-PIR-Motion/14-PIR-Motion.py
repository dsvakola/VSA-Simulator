"""
  PIR Motion Alarm
  Lights an LED and prints a message when the PIR sensor sees motion.

  A PIR sensor's OUT pin goes high when it sees a warm body move.
  In VSA Simulator, click the sensor and tick "Motion".

  The circuit:
  - PIR VCC -> VIN, GND -> GND
  - PIR OUT -> D5 (GPIO14)
  - LED: D6 (GPIO12) -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 11 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 30 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin

pir = Pin(14, Pin.IN)
led = Pin(12, Pin.OUT)
last_state = 0   # so we print only when something changes

while True:
    motion = pir.value()
    led.value(motion)   # the LED follows the sensor
    if motion != last_state:
        if motion == 1:
            print("Motion detected!")
        else:
            print("All quiet.")
        last_state = motion
