/*
  Potentiometer to Serial Monitor (AVR Studio style, plain C)
  Reads a potentiometer (0 to 1023) and prints the value and the voltage.

  AVR chips such as the ATmega128 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 04, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 04-Potentiometer. Turn the knob while simulating:
  click the potentiometer to open its slider.

  The circuit:
  - Potentiometer: left leg -> +5 V, right leg -> GND, middle (wiper) -> PF0

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega128, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega128 -DF_CPU=16000000UL -Os -o main.elf main.c
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

int main(void)
{
    uart_init();
    adc_init();

    while (1)
    {
        uint16_t value = adc_read(0);               // PF0 is ADC channel 0
        uint32_t mv = (uint32_t)value * 5000 / 1023;       // millivolts

        uart_puts("Value: ");
        uart_putnum(value);
        uart_puts("   Voltage: ");
        uart_putnum(mv / 1000);                            // whole volts
        uart_putc('.');
        uart_putnum((mv % 1000) / 100);                    // first decimal
        uart_putnum((mv % 100) / 10);                      // second decimal
        uart_puts(" V\r\n");
        _delay_ms(500);
    }
}
