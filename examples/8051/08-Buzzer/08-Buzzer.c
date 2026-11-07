/*
  Buzzer
  Beeps an active buzzer three times, then waits, and repeats.

  An active buzzer makes its tone by itself when it gets power, so
  the program only has to switch the pin on and off.

  The circuit:
  - +5 V -> buzzer + (long leg), buzzer - -> P1.0
    (the pin LOW switches the buzzer on)

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
    for (i = 0; i < 3; i++) {
      P1_0 = 0;           // buzzer on (pin LOW)
      delay_ms(200);
      P1_0 = 1;           // buzzer off (pin HIGH)
      delay_ms(200);
    }
    delay_ms(1500);       // pause before the next three beeps
  }
}
