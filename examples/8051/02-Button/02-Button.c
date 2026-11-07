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

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 10 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 27 October 2026 by Prof. Yash D. Vidyasagar

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

void main(void) {
  unsigned char last = 1;  // last button state (1 = released), to print only changes
  P1_7 = 1;            // write 1 first, so the pin can be used as an input
  serial_init();       // start the serial port so the program can print
  while (1) {
    if (P1_7 == 0) {   // 0 means the button is pressed
      P1_0 = 0;        // LED on (pin LOW)
    } else {
      P1_0 = 1;        // LED off (pin HIGH)
    }
    if (P1_7 != last) {            // the state changed: print it once
      if (P1_7 == 0) send_text("Button pressed: LED on\r\n");
      else send_text("Button released: LED off\r\n");
      last = P1_7;
    }
  }
}
