/*
  Bare ATmega8 chip with crystal and reset (AVR Studio style, plain C)
  Blinks an LED on PB0 of a bare ATmega8 chip wired on the breadboard, as on a real circuit board.

  AVR chips such as the ATmega8 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 11, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  How to wire a bare ATmega8:
  - Power: VCC (pin 7) and AVCC (pin 20) -> +5 V; GND (pins 8 and 22) -> GND
  - Crystal 16 MHz between XTAL1 (pin 9) and XTAL2 (pin 10), with a 22 pF
    capacitor from each to GND (the 3-leg crystal part has both capacitors built in)
  - Reset: RESET (pin 1) has a pull-up resistor inside; a push button from RESET to GND resets the chip
  - LED: PB0 (pin 14) -> 220 ohm resistor -> LED anode, LED cathode -> GND

  How to build it:
  - AVR Studio: New Project > GCC C Executable Project, device ATmega8, paste this code,
    build with F7 and load the .hex file in VSA Simulator (clock 16 MHz).
  - Or with avr-gcc: avr-gcc -mmcu=atmega8 -DF_CPU=16000000UL -Os -o main.elf main.c
    then avr-objcopy -O ihex -R .eeprom main.elf main.hex

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 05 October 2026 by Prof. Dattaraj S. Vidyasagar
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
