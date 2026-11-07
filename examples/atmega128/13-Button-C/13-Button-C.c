/*
  Push Button and LED (AVR Studio style, plain C)
  Lights the LED while the push button is pressed.

  AVR chips such as the ATmega128 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 02, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 02-Button. The button pin uses the chip's own pull-up
  resistor, so it reads 1 when the button is released and 0 when it is
  pressed. In VSA Simulator, press and hold the button with the mouse.

  The circuit:
  - Push button: one side -> PC0, other side -> GND
  - LED: PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

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

int main(void)
{
    DDRB |= (1 << PB0);          // LED pin = output
    DDRC &= ~(1 << PC0);         // button pin = input
    PORTC |= (1 << PC0);         // switch the pull-up resistor on

    while (1)
    {
        if (!(PINC & (1 << PC0)))        // 0 means: pressed
            PORTB |= (1 << PB0);         // LED on
        else
            PORTB &= ~(1 << PB0);        // LED off
    }
}
