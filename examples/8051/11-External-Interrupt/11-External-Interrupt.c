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

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 13 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 31 October 2026 by Prof. Yash D. Vidyasagar

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

volatile unsigned char count = 0;
volatile unsigned char changed = 0; // set by the interrupt routine, so main() can print the new count

// The interrupt routine of INT0 (interrupt number 0).
#ifdef __SDCC
void int0_isr(void) __interrupt(0)
#else
void int0_isr(void) interrupt 0
#endif
{
  count = (count + 1) & 0x0F;   // 0..15, then back to 0
  P1 = 0xF0 | (~count & 0x0F);  // show it on the LEDs (LOW = LED on)
  changed = 1;                  // tell main() to print the count
}

void main(void) {
  P1 = 0xFF;    // all LEDs off
  serial_init(); // start the serial port so the program can print
  IT0 = 1;      // INT0 reacts to a falling edge (button pressed)
  EX0 = 1;      // allow the INT0 interrupt
  EA = 1;       // allow interrupts
  while (1) {   // the interrupt does the counting, main() only prints it
    if (changed) {
      changed = 0;
      send_text("Button pressed, count = ");
      send_number(count);
      send_text("\r\n");
    }
  }
}
