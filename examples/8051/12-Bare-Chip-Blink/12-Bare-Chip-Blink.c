/*
  Bare 8051 chip (AT89S52) with crystal and reset
  Blinks an LED on P1.0 of a bare AT89S52 chip wired on the breadboard, as on a real circuit board.

  How to wire a bare 8051 (the same wiring works for AT89C51, AT89C52, AT89S51 and AT89S52):
  - Power: VCC (pin 40) -> +5 V, GND (pin 20) -> GND
  - EA (pin 31) -> +5 V, so the chip runs the program inside it
  - Crystal 11.0592 MHz between XTAL1 (pin 19) and XTAL2 (pin 18), with a
    22 pF capacitor from each to GND (the 3-leg crystal part has both capacitors built in)
  - Reset: RST (pin 9) -> 8.2 k resistor -> GND, and a push button from RST to +5 V
  - LED: +5 V -> 220 ohm resistor -> LED anode, LED cathode -> P1.0 (pin 1)
  The program is the same as 01-Blink.

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
// Waits for "ms" milliseconds using Timer 0 (11.0592 MHz crystal).
// One machine cycle = 12 / 11.0592 MHz, so 922 cycles are about 1 ms.
void delay_ms(unsigned int ms) {
  while (ms--) {
    TMOD = (TMOD & 0xF0) | 0x01;   // Timer 0, mode 1 (16-bit timer)
    TH0 = 0xFC;                    // 65536 - 922 = 0xFC66
    TL0 = 0x66;
    TR0 = 1;                       // start the timer
    while (!TF0) { }               // wait until it overflows
    TR0 = 0;                       // stop it
    TF0 = 0;                       // clear the flag for next time
  }
}

void main(void) {
  while (1) {
    P1_0 = 0;          // LED on (the pin goes LOW)
    delay_ms(1000);
    P1_0 = 1;          // LED off (the pin goes HIGH)
    delay_ms(1000);
  }
}
