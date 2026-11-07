/*
  Servo Sweep (AVR Studio style, plain C)
  Sweeps a servo arm from 0 to 180 degrees and back.

  AVR chips such as the ATmega16 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 07, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 07-Servo-Sweep. A servo wants a pulse every 20 ms;
  the pulse length sets the angle (544 us = 0 degrees, 2400 us = 180
  degrees). Here the pulses are made by the program itself.

  The circuit:
  - Servo GND (brown or black) -> GND
  - Servo V+ (red) -> +5 V
  - Servo SIGNAL (orange or yellow) -> PB1

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega16, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 27 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 18 October 2026 by Prof. Yash D. Vidyasagar

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

// _delay_us() needs a fixed number, so a longer wait is made of 10 us pieces.
static void delay_us_var(uint16_t us)
{
    while (us >= 10)
    {
        _delay_us(10);
        us -= 10;
    }
}

// Moves the servo to an angle (0 to 180) by sending 5 pulses.
static void move_servo(uint8_t angle)
{
    uart_puts("Servo angle: ");               // print the angle in the Serial Monitor
    uart_putnum(angle);
    uart_puts("\r\n");
    uint16_t pulse = 544 + (uint32_t)angle * (2400 - 544) / 180;   // pulse length in microseconds
    // (uint32_t: angle * 1856 is bigger than 65535, so 16-bit maths would overflow)

    for (uint8_t i = 0; i < 5; i++)
    {
        PORTB |= (1 << PB1);     // pulse high
        delay_us_var(pulse);
        PORTB &= ~(1 << PB1);    // pulse low
        _delay_ms(20);                          // the rest of the 20 ms period
    }
}

int main(void)
{
    DDRB |= (1 << PB1);          // servo signal pin = output
    uart_init();                                // start the serial port so the program can print

    while (1)
    {
        for (int16_t angle = 0; angle <= 180; angle += 10)      // 0 to 180 degrees
            move_servo(angle);
        for (int16_t angle = 180; angle >= 0; angle -= 10)      // and back
            move_servo(angle);
    }
}
