/*
  LDR Night Light (AVR Studio style, plain C)
  Switches an LED on when the room gets dark.

  AVR chips such as the ATmega32 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 05, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 05-LDR-Night-Light. The LDR and a 10 k resistor form
  a voltage divider: bright light gives a high reading, dark a low one.
  Click the LDR while simulating to change the light.

  The circuit:
  - +5 V -> LDR -> PA0 -> 10 k resistor -> GND
  - PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega32, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Modified 03 November 2026 by Prof. Dattaraj S. Vidyasagar
  Modified 04 November 2026 by Prof. Yash D. Vidyasagar

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

static void uart_puts(const char *s)
{
    while (*s)
        uart_putc(*s++);
}

static void uart_putnum(long n)                   // prints a whole number
{
    char buf[12];
    int i = 0;
    if (n < 0) { uart_putc('-'); n = -n; }
    if (n == 0) buf[i++] = '0';
    while (n > 0) { buf[i++] = '0' + (n % 10); n /= 10; }
    while (i > 0) uart_putc(buf[--i]);
}

// ---- analog-to-digital converter (ADC) -----------------------------------
static void adc_init(void)
{
    ADMUX = (1 << REFS0);                                    // reference = AVCC (5 V)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   // ADC on, clock / 128
}

static uint16_t adc_read(uint8_t channel)
{
    ADMUX = (1 << REFS0) | (channel & 0x07);                 // choose the input pin
    ADCSRA |= (1 << ADSC);                                   // start a conversion
    while (ADCSRA & (1 << ADSC))
        ;                                                    // wait until it is done
    return ADC;                                              // 0 to 1023
}

#define DARK_LEVEL 300                      // below this reading we call it "dark"

int main(void)
{
    DDRB |= (1 << PB0);          // LED pin = output
    uart_init();
    adc_init();

    while (1)
    {
        uint16_t light = adc_read(0);   // high = bright, low = dark

        uart_puts("Light level: ");
        uart_putnum(light);
        uart_puts("\r\n");

        if (light < DARK_LEVEL)
            PORTB |= (1 << PB0);    // dark: light on
        else
            PORTB &= ~(1 << PB0);   // bright: light off
        _delay_ms(300);
    }
}
