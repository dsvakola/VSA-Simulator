/*
  Timer 0 Delay
  Toggles an LED every 500 ms, timed by Timer 0 running by itself.

  Instead of waiting in a loop, Timer 0 counts in the background and
  raises an interrupt every 50 ms. The program counts 10 of them (500 ms)
  and then toggles the LED on P1.0. The main loop is free for other work.

  The circuit:
  - +5 V -> 220 ohm resistor -> LED anode, LED cathode -> P1.0

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 22 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 19 October 2026 by Prof. Yash D. Vidyasagar

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

// ---- serial port: 9600 baud, so the program can print in the Serial Monitor ----
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

// Prints a whole number (0 to 65535) as text.
void send_number(unsigned int n) {
  char digits[5];
  unsigned char i = 0;
  do {
    digits[i++] = '0' + n % 10;  // collect the digits, last one first
    n /= 10;
  } while (n);
  while (i) send_char(digits[--i]);
}

volatile unsigned char ticks = 0;   // counts 50 ms steps

// The interrupt routine of Timer 0 (interrupt number 1).
#ifdef __SDCC
void timer0_isr(void) __interrupt(1)
#else
void timer0_isr(void) interrupt 1
#endif
{
  TH0 = 0x4C;           // reload 65536 - 46080 = 0x4C00 (about 50 ms)
  TL0 = 0x00;
  ticks++;
}

void main(void) {
  serial_init();                 // start the serial port (it uses Timer 1)
  TMOD = (TMOD & 0xF0) | 0x01;   // Timer 0, mode 1 (16-bit)
  TH0 = 0x4C;
  TL0 = 0x00;
  ET0 = 1;                       // allow the Timer 0 interrupt
  EA = 1;                        // allow interrupts
  TR0 = 1;                       // start the timer

  while (1) {
    if (ticks >= 10) {           // 10 x 50 ms = 500 ms
      ticks = 0;
      P1_0 = !P1_0;              // toggle the LED
      if (P1_0) send_text("LED off\r\n");   // print the new state (the pin LOW = LED on)
      else send_text("LED on\r\n");
    }
  }
}
