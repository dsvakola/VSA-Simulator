/*
  Blink (AVR Studio style, plain C)
  Turns an LED on for one second, then off for one second, repeatedly.

  AVR chips such as the ATmega32 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 01, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 01-Blink, written in plain C instead of Arduino style.
  The circuit:
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

int main(void)
{
    DDRB |= (1 << PB0);          // make PB0 an output

    while (1)
    {
        PORTB |= (1 << PB0);     // LED on
        _delay_ms(1000);                    // wait one second
        PORTB &= ~(1 << PB0);    // LED off
        _delay_ms(1000);
    }
}
