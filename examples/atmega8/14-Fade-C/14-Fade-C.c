/*
  Fade (AVR Studio style, plain C)
  Fades an LED smoothly up and down with a timer in PWM mode.

  AVR chips such as the ATmega8 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 03, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 03-Fade. A timer makes pulses on PB1; the longer
  the pulses, the brighter the LED. The duty cycle is set in OCR1A.

  The circuit:
  - PB1 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega8, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega8 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 13 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 05 November 2026 by Prof. Yash D. Vidyasagar

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

int main(void)
{
    int16_t brightness = 0;                 // 0 (off) to 255 (fully on)
    int16_t step = 5;

    DDRB |= (1 << PB1);                                     // OC1A (PB1) = output
    TCCR1A = (1 << COM1A1) | (1 << WGM10);                  // timer 1: 8-bit PWM on OC1A
    TCCR1B = (1 << CS11);                                   // clock / 8
    uart_init();                            // start the serial port so the program can print

    while (1)
    {
        OCR1A = brightness;             // set the pulse length
        brightness += step;
        if (brightness <= 0 || brightness >= 255)
        {
            step = -step;                   // turn around at the ends
            uart_puts("Brightness ");       // print a line in the Serial Monitor
            uart_putnum(brightness);
            uart_puts(step > 0 ? ": getting brighter\r\n" : ": getting dimmer\r\n");
        }
        _delay_ms(30);
    }
}
