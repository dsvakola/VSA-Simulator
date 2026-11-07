/*
  7-Segment Display (FND507, common anode)
  Counts from 0 to 9 on a common-anode 7-segment display.

  The display has a common anode (COM) and a LOW pin lights a segment,
  the same sink wiring as the LEDs: 8051 pins pull LOW strongly. The
  segments a, b, c, d, e, f, g are on P1.0 to P1.6.

  The circuit:
  - COM -> 330 ohm resistor -> +5 V
  - P1.0 -> segment A, P1.1 -> B, P1.2 -> C, P1.3 -> D, P1.4 -> E,
    P1.5 -> F, P1.6 -> G

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

// Bit pattern for each digit: bit 0 is segment a ... bit 6 is segment g.
const unsigned char digits[10] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void main(void) {
  unsigned char n = 0;
  while (1) {
    P1 = ~digits[n];    // show the digit (a segment lights when its pin is LOW)
    delay_ms(1000);
    n++;
    if (n > 9) n = 0;   // after 9 start again at 0
  }
}
