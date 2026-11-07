"""
  Servo Sweep
  Turns a servo motor arm from 0 to 180 degrees and back again.

  A hobby servo reads a pulse 50 times a second. A short pulse
  (0.54 ms) turns the arm to 0 degrees, a long pulse (2.4 ms) to 180
  degrees. The program works out the pulse for each angle.

  The servo needs 5 V, so it takes its power from the VIN pin.

  The circuit:
  - Servo signal (orange) -> D18 (GPIO18)
  - Servo V+ (red) -> VIN
  - Servo GND (brown) -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 09 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 04 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin, PWM
import time

servo = PWM(Pin(18))
servo.freq(50)   # 50 pulses every second, one every 20 ms

def set_angle(angle):
    """Turns the arm to `angle` degrees (0 to 180)."""
    pulse_us = 544 + (2400 - 544) * angle // 180   # 544 to 2400 microseconds
    servo.duty_u16(pulse_us * 65535 // 20000)      # share of the 20 ms cycle

while True:
    for angle in range(0, 181):        # 0 to 180 degrees, one at a time
        set_angle(angle)
        if angle % 10 == 0:              # print every 10 degrees
            print("Servo angle:", angle, "degrees")
        time.sleep_ms(15)              # give the arm time to get there
    for angle in range(180, -1, -1):   # and back again
        set_angle(angle)
        if angle % 10 == 0:              # print every 10 degrees
            print("Servo angle:", angle, "degrees")
        time.sleep_ms(15)
