/*
  Buzzer (AVR Studio style, plain C)
  Beeps an active buzzer three times, then waits, and repeats.

  AVR chips such as the ATmega32 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 06, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 06-Buzzer. An active buzzer makes its tone by itself
  when it gets power, so the program only switches the pin on and off.

  The circuit:
  - PB0 -> buzzer + (long leg), buzzer - -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega32, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 01 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 03 November 2026 by Prof. Yash D. Vidyasagar

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
    UBRRH = (uint8_t)(BAUD_REG >> 8);
    UBRRL = (uint8_t)BAUD_REG;
    UCSRB = (1 << RXEN) | (1 << TXEN);      // switch the receiver and transmitter on
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);   // 8 data bits, no parity, 1 stop bit
}

static void uart_putc(char c)
{
    while (!(UCSRA & (1 << UDRE)))
        ;                                         // wait until the transmit register is free
    UDR = c;
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

// One beep of 150 ms, followed by 150 ms of silence.
static void beep(void)
{
    uart_puts("Beep!\r\n");                 // print a line in the Serial Monitor
    PORTB |= (1 << PB0);         // buzzer on
    _delay_ms(150);
    PORTB &= ~(1 << PB0);        // buzzer off
    _delay_ms(150);
}

int main(void)
{
    DDRB |= (1 << PB0);          // buzzer pin = output
    uart_init();                            // start the serial port so the program can print

    while (1)
    {
        for (uint8_t i = 0; i < 3; i++)
            beep();                         // three quick beeps ...
        uart_puts("Pause\r\n");
        _delay_ms(1500);                    // ... then a pause
    }
}
