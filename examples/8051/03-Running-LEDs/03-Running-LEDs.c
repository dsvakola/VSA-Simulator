/*
  Running LEDs
  Eight LEDs on port 1 light one after the other, forward and back (knight rider).

  The circuit:
  - +5 V -> 220 ohm resistor -> LED anode, LED cathode -> P1.x
    (the same for all eight pins P1.0 to P1.7; a LOW pin lights its LED)

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
  unsigned char i;
  while (1) {
    // Move the light from P1.0 to P1.7 ...
    for (i = 0; i < 8; i++) {
      P1 = (unsigned char)~(1 << i);  // only bit "i" is 0, so only one LED is on
      delay_ms(150);
    }
    // ... and back again.
    for (i = 6; i > 0; i--) {
      P1 = (unsigned char)~(1 << i);
      delay_ms(150);
    }
  }
}
