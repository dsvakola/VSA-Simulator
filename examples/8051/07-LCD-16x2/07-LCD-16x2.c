/*
  LCD 16x2 (4-bit mode)
  Shows a message and a seconds counter on a 16x2 LCD wired directly to port 2.

  The LCD works in 4-bit mode, so only six wires are needed:
  RS -> P2.0, E -> P2.1, D4 -> P2.2, D5 -> P2.3, D6 -> P2.4, D7 -> P2.5.
  RW goes to GND (we only write). VSS and K go to GND, VDD and A to
  +5 V. V0 (contrast) goes to GND for dark, clear letters.

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 07 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 06 November 2026 by Prof. Yash D. Vidyasagar

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

#define RS P2_0
#define EN P2_1

// Sends the lower 4 bits of "n" to the LCD data pins D4..D7 (P2.2..P2.5).
void lcd_nibble(unsigned char n) {
  P2 = (P2 & 0xC3) | ((n & 0x0F) << 2);
  EN = 1;
  delay_ms(1);
  EN = 0;
  delay_ms(1);
}

void lcd_write(unsigned char value, unsigned char is_data) {
  RS = is_data;
  lcd_nibble(value >> 4);      // high half first
  lcd_nibble(value);           // then the low half
}

void lcd_init(void) {
  delay_ms(50);
  RS = 0;
  lcd_nibble(0x03);            // the start-up sequence from the LCD data sheet
  lcd_nibble(0x03);
  lcd_nibble(0x03);
  lcd_nibble(0x02);            // switch to 4-bit mode
  lcd_write(0x28, 0);          // 4-bit, 2 lines, 5x8 dots
  lcd_write(0x0C, 0);          // display on, cursor off
  lcd_write(0x06, 0);          // cursor moves right
  lcd_write(0x01, 0);          // clear the screen
  delay_ms(2);
}

void lcd_text(const char *s) {
  while (*s) lcd_write(*s++, 1);
}

void main(void) {
  unsigned int seconds = 0;
  serial_init();               // start the serial port so the program can print
  lcd_init();
  lcd_write(0x80, 0);          // first line
  lcd_text("VSA Simulator");
  while (1) {
    lcd_write(0xC0, 0);        // second line
    lcd_text("Seconds: ");
    lcd_write('0' + (seconds / 100) % 10, 1);
    lcd_write('0' + (seconds / 10) % 10, 1);
    lcd_write('0' + seconds % 10, 1);
    send_text("Seconds: ");    // print the same number in the Serial Monitor
    send_number(seconds);
    send_text("\r\n");
    seconds++;
    delay_ms(1000);
  }
}
