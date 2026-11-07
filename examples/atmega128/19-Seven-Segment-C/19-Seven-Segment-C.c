/*
  7-Segment Display FND500 (AVR Studio style, plain C)
  Counts from 0 to 9 on a common-cathode 7-segment display.

  AVR chips such as the ATmega128 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 08, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 08-Seven-Segment. The common pin (COM) goes to GND
  through one 330 ohm resistor and a 1 on a segment pin lights that segment.

  The circuit:
  - PA0 -> segment A, PA1 -> segment B, PA2 -> segment C, PA3 -> segment D, PA4 -> segment E, PA5 -> segment F, PA6 -> segment G
  - COM -> 330 ohm resistor -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega128, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega128 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 08 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 26 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#ifndef F_CPU
#define F_CPU 16000000UL      // the chip runs from a 16 MHz crystal
#endif
#include <avr/io.h>
#include <util/delay.h>

// ---- serial port (UART): 9600 baud -------------------------------------
#define BAUD_REG ((F_CPU / 16 / 9600) - 1)      // 103 for 16 MHz

static void uart_init(void)
{
    UBRR0H = (uint8_t)(BAUD_REG >> 8);
    UBRR0L = (uint8_t)BAUD_REG;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);      // switch the receiver and transmitter on
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);               // 8 data bits, no parity, 1 stop bit
}

static void uart_putc(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;                                         // wait until the transmit register is free
    UDR0 = c;
}

__attribute__((unused)) static void uart_puts(const char *s)
{
    while (*s)
        uart_putc(*s++);
}

__attribute__((unused)) static void uart_putnum(long n)                   // prints a whole number
{
    char buf[12];
    int i = 0;
    if (n < 0) { uart_putc('-'); n = -n; }
    if (n == 0) buf[i++] = '0';
    while (n > 0) { buf[i++] = '0' + (n % 10); n /= 10; }
    while (i > 0) uart_putc(buf[--i]);
}

// Which segments are lit for each digit: bit 0 = a, bit 1 = b ... bit 6 = g.
static const uint8_t digits[10] = {
    0x3F,   // 0
    0x06,   // 1
    0x5B,   // 2
    0x4F,   // 3
    0x66,   // 4
    0x6D,   // 5
    0x7D,   // 6
    0x07,   // 7
    0x7F,   // 8
    0x6F    // 9
};

// Segments a..g are on PA0..PA6, all in one port, so one write sets the whole digit.
static void segments_init(void)
{
    DDRA |= 0x7F;                          // PA0..PA6 = outputs
}

static void show_digit(uint8_t n)
{
    PORTA = (PORTA & 0x80) | digits[n];     // bit 0 = a ... bit 6 = g
}

int main(void)
{
    segments_init();
    uart_init();                            // start the serial port so the program can print

    while (1)
    {
        for (uint8_t n = 0; n <= 9; n++)
        {
            show_digit(n);
            uart_puts("Digit: ");           // print the digit in the Serial Monitor
            uart_putnum(n);
            uart_puts("\r\n");
            _delay_ms(1000);
        }
    }
}
