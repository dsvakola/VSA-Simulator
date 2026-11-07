/*
  7-Segment Display FND500 (AVR Studio style, plain C)
  Counts from 0 to 9 on a common-cathode 7-segment display.

  AVR chips such as the ATmega8 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 08, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 08-Seven-Segment. The common pin (COM) goes to GND
  through one 330 ohm resistor and a 1 on a segment pin lights that segment.

  The circuit:
  - PD2 -> segment A, PD3 -> segment B, PD4 -> segment C, PD5 -> segment D, PD6 -> segment E, PD7 -> segment F, PB0 -> segment G
  - COM -> 330 ohm resistor -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega8, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega8 -DF_CPU=16000000UL -Os -o main.elf main.c
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

// Segments a..f are on PD2..PD7 and segment g is on PB0.
static void segments_init(void)
{
    DDRD |= 0xFC;                           // PD2..PD7 = outputs
    DDRB |= (1 << PB0);                     // PB0 = output
}

static void show_digit(uint8_t n)
{
    uint8_t p = digits[n];
    PORTD = (PORTD & 0x03) | ((p & 0x3F) << 2);     // segments a..f -> PD2..PD7
    if (p & 0x40)
        PORTB |= (1 << PB0);                        // segment g -> PB0
    else
        PORTB &= ~(1 << PB0);
}

int main(void)
{
    segments_init();

    while (1)
    {
        for (uint8_t n = 0; n <= 9; n++)
        {
            show_digit(n);
            _delay_ms(1000);
        }
    }
}
