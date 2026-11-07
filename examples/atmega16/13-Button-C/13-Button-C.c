/*
  Push Button and LED (AVR Studio style, plain C)
  Lights the LED while the push button is pressed.

  AVR chips such as the ATmega16 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 02, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 02-Button. The button pin uses the chip's own pull-up
  resistor, so it reads 1 when the button is released and 0 when it is
  pressed. In VSA Simulator, press and hold the button with the mouse.

  The circuit:
  - Push button: one side -> PD2, other side -> GND
  - LED: PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega16, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 26 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 29 October 2026 by Prof. Yash D. Vidyasagar

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
    uint8_t last = 1;                       // last button state (1 = released), to print only changes

    DDRB |= (1 << PB0);          // LED pin = output
    DDRD &= ~(1 << PD2);         // button pin = input
    PORTD |= (1 << PD2);         // switch the pull-up resistor on
    uart_init();                            // start the serial port so the program can print

    while (1)
    {
        uint8_t state = (PIND & (1 << PD2)) ? 1 : 0;
        if (state == 0)                             // 0 means: pressed
            PORTB |= (1 << PB0);         // LED on
        else
            PORTB &= ~(1 << PB0);        // LED off

        if (state != last)                          // the state changed: print it once
        {
            if (state == 0)
                uart_puts("Button pressed: LED on\r\n");
            else
                uart_puts("Button released: LED off\r\n");
            last = state;
        }
    }
}
