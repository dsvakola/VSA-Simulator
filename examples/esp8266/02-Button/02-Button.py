"""
  Push Button and LED
  Lights the LED while the push button is pressed.

  The button pin uses the ESP8266 NodeMCU's own pull-up resistor (Pin.PULL_UP), so
  no extra resistor is needed for the button. The pin reads 1 when the
  button is released and 0 when it is pressed.
  In VSA Simulator, press and hold the button with the mouse while
  simulating.

  The circuit:
  - Push button: one side -> D5 (GPIO14), other side -> GND
  - LED: D6 (GPIO12) -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Shell, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 02 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 23 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin

button = Pin(14, Pin.IN, Pin.PULL_UP)   # 1 when released, 0 when pressed
led = Pin(12, Pin.OUT)

was_pressed = False   # remembers the last state, so a message is printed only when it changes

while True:
    # 0 means the button is pressed (it connects the pin to GND).
    pressed = (button.value() == 0)
    if pressed:
        led.value(1)   # pressed: LED on
    else:
        led.value(0)   # released: LED off

    if pressed != was_pressed:   # the state changed: print it once
        print("Button pressed: LED on" if pressed else "Button released: LED off")
        was_pressed = pressed
