"""
  DC Motor with a Transistor
  Speeds a DC motor up and slows it down again with PWM.

  A GPIO pin cannot give enough current for a motor, so an NPN transistor
  switches the motor's own 9 V battery. The diode across the motor
  protects the transistor from the voltage spike when the motor stops.

  The circuit:
  - D6 (GPIO12) -> 1 k resistor -> transistor base
  - Transistor emitter -> GND
  - Transistor collector -> motor -> 9 V battery +
  - Diode across the motor (stripe towards battery +)
  - 9 V battery - -> GND

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

motor = PWM(Pin(12))
motor.freq(1000)

while True:
    for speed in range(0, 65536, 1285):     # speed up from stop to full speed
        motor.duty_u16(speed)
        time.sleep_ms(40)
    print("Full speed")
    time.sleep(2)
    for speed in range(65535, -1, -1285):   # slow down to a stop
        motor.duty_u16(speed)
        time.sleep_ms(40)
    print("Stopped")
    time.sleep(2)
