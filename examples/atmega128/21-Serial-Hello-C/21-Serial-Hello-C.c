/*
  Serial Hello (AVR Studio style, plain C)
  Sends a message and a counter to the Serial Monitor and echoes what you type.

  AVR chips such as the ATmega128 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 10, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 10-Serial-Hello. Open the Serial Monitor in VSA
  Simulator, type a letter and press Send: the program sends it back.

  The circuit: none needed (the Serial Monitor is built in).

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega128, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega128 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 04 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 27 October 2026 by Prof. Yash D. Vidyasagar

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

int main(void)
{
    uint16_t counter = 0;

    uart_init();                                    // start the serial port at 9600 baud
    uart_puts("Hello from the ATmega128!\r\n");

    while (1)
    {
        // Wait one second, but look for typed characters every 10 ms.
        for (uint8_t i = 0; i < 100; i++)
        {
            if (UCSR0A & (1 << RXC0))                // a character was typed
            {
                char c = UDR0;
                uart_puts("You typed: ");
                uart_putc(c);
                uart_puts("\r\n");
            }
            _delay_ms(10);
        }

        uart_puts("Count: ");
        uart_putnum(counter);
        uart_puts("\r\n");
        counter++;
    }
}
