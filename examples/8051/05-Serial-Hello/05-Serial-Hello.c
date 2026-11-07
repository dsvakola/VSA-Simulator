/*
  Serial Hello
  Sends a counter message to the Serial Monitor every second and echoes what you type.

  The serial port runs at 9600 baud, using Timer 1 as the baud rate
  generator (11.0592 MHz crystal). Open the Serial Monitor in VSA
  Simulator, type a letter and press Send: the program sends it back.

  The circuit: none needed (the Serial Monitor is built in).

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

void serial_init(void) {
  TMOD = (TMOD & 0x0F) | 0x20;   // Timer 1, mode 2 (8-bit auto-reload)
  TH1 = 0xFD;                    // 9600 baud at 11.0592 MHz
  TL1 = 0xFD;
  SCON = 0x50;                   // 8-bit serial, receiver on
  TR1 = 1;                       // start Timer 1
}

void send_char(char c) {
  SBUF = c;                      // send the character
  while (!TI) { }                // wait until it has been sent
  TI = 0;
}

void send_text(const char *s) {
  while (*s) send_char(*s++);
}

void main(void) {
  unsigned char n = 0;
  unsigned char waited = 0;
  serial_init();
  send_text("Hello from the 8051!\r\n");
  while (1) {
    if (RI) {                    // a character was typed
      RI = 0;
      send_text("You typed: ");
      send_char(SBUF);
      send_text("\r\n");
    }
    delay_ms(10);
    if (++waited >= 100) {       // 100 x 10 ms = 1 second
      waited = 0;
      send_text("Count: ");
      send_char('0' + n / 10);
      send_char('0' + n % 10);
      send_text("\r\n");
      n = (n + 1) % 100;
    }
  }
}
