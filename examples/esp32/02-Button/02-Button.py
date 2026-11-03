"""
  Push Button and LED
  Lights the LED while the push button is pressed.

  The button pin uses the ESP32 DevKit's own pull-up resistor (Pin.PULL_UP), so
  no extra resistor is needed for the button. The pin reads 1 when the
  button is released and 0 when it is pressed.
  In VSA Simulator, press and hold the button with the mouse while
  simulating.

  The circuit:
  - Push button: one side -> D14 (GPIO14), other side -> GND
  - LED: D13 (GPIO13) -> 220 ohm resistor -> LED anode, LED cathode -> GND

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

button = Pin(14, Pin.IN, Pin.PULL_UP)   # 1 when released, 0 when pressed
led = Pin(13, Pin.OUT)

while True:
    # 0 means the button is pressed (it connects the pin to GND).
    if button.value() == 0:
        led.value(1)   # pressed: LED on
    else:
        led.value(0)   # released: LED off
