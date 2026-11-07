/*
  Buzzer (AVR Studio style, plain C)
  Beeps an active buzzer three times, then waits, and repeats.

  AVR chips such as the ATmega8 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 06, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 06-Buzzer. An active buzzer makes its tone by itself
  when it gets power, so the program only switches the pin on and off.

  The circuit:
  - PB0 -> buzzer + (long leg), buzzer - -> GND

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

// One beep of 150 ms, followed by 150 ms of silence.
static void beep(void)
{
    PORTB |= (1 << PB0);         // buzzer on
    _delay_ms(150);
    PORTB &= ~(1 << PB0);        // buzzer off
    _delay_ms(150);
}

int main(void)
{
    DDRB |= (1 << PB0);          // buzzer pin = output

    while (1)
    {
        for (uint8_t i = 0; i < 3; i++)
            beep();                         // three quick beeps ...
        _delay_ms(1500);                    // ... then a pause
    }
}
