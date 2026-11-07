/*
  Push Button and LED
  Lights the LED while the push button is pressed.

  The pins of port 1 have a small pull-up resistor inside, so no
  extra resistor is needed for the button: the pin reads 1 when the
  button is released and 0 when it is pressed.
  In VSA Simulator, press and hold the button with the mouse.

  The circuit:
  - Push button: one side -> P1.7, other side -> GND
  - LED: +5 V -> 220 ohm resistor -> LED anode, LED cathode -> P1.0
    (the pin LOW switches the LED on)

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Modified 03 November 2026 by Prof. Dattaraj S. Vidyasagar
  Modified 04 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#ifdef __SDCC
#include <8052.h>      // SDCC
#else
#include <reg52.h>     // Keil
#endif

void main(void) {
  P1_7 = 1;            // write 1 first, so the pin can be used as an input
  while (1) {
    if (P1_7 == 0) {   // 0 means the button is pressed
      P1_0 = 0;        // LED on (pin LOW)
    } else {
      P1_0 = 1;        // LED off (pin HIGH)
    }
  }
}
