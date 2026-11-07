/*
  External Interrupt INT0 Counter
  Counts button presses with the INT0 interrupt and shows the count in binary on four LEDs.

  Pressing the button pulls P3.2 (INT0) low. The falling edge raises
  an interrupt, and the interrupt routine adds one to the counter. The
  count 0 to 15 is shown on the LEDs P1.0 (lowest bit) to P1.3. A LED
  is on when its pin is LOW, so the program sends the count inverted.

  The circuit:
  - Push button: one side -> P3.2, other side -> GND
  - +5 V -> 220 ohm resistor -> LED anode, LED cathode -> P1.0 to P1.3
    (four LEDs with a resistor each)

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

volatile unsigned char count = 0;

// The interrupt routine of INT0 (interrupt number 0).
#ifdef __SDCC
void int0_isr(void) __interrupt(0)
#else
void int0_isr(void) interrupt 0
#endif
{
  count = (count + 1) & 0x0F;   // 0..15, then back to 0
  P1 = 0xF0 | (~count & 0x0F);  // show it on the LEDs (LOW = LED on)
}

void main(void) {
  P1 = 0xFF;    // all LEDs off
  IT0 = 1;      // INT0 reacts to a falling edge (button pressed)
  EX0 = 1;      // allow the INT0 interrupt
  EA = 1;       // allow interrupts
  while (1) { } // nothing else to do: the interrupt does the work
}
