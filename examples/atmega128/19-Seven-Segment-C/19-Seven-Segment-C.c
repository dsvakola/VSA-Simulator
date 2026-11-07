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

    while (1)
    {
        for (uint8_t n = 0; n <= 9; n++)
        {
            show_digit(n);
            _delay_ms(1000);
        }
    }
}
