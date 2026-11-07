/*
  Relay Module
  Clicks a relay module on for 2 seconds and off for 2 seconds.

  The relay module has its own driver, so its IN pin can be connected
  straight to the microcontroller. Most relay modules switch ON when the
  IN pin is LOW (and OFF when it is HIGH).

  The circuit:
  - Relay VCC -> +5 V, GND -> GND
  - Relay IN -> P1.0

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
    P1_0 = 0;            // relay on (IN pin LOW)
    delay_ms(2000);
    P1_0 = 1;            // relay off (IN pin HIGH)
    delay_ms(2000);
  }
}
