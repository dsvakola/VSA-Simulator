/*
  Fade (AVR Studio style, plain C)
  Fades an LED smoothly up and down with a timer in PWM mode.

  AVR chips such as the ATmega128 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 03, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 03-Fade. A timer makes pulses on PB4; the longer
  the pulses, the brighter the LED. The duty cycle is set in OCR0.

  The circuit:
  - PB4 -> 220 ohm resistor -> LED anode, LED cathode -> GND

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
    int16_t brightness = 0;                 // 0 (off) to 255 (fully on)
    int16_t step = 5;

    DDRB |= (1 << PB4);                                     // OC0 (PB4) = output
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);   // timer 0: fast PWM, clock / 8

    while (1)
    {
        OCR0 = brightness;             // set the pulse length
        brightness += step;
        if (brightness <= 0 || brightness >= 255)
            step = -step;                   // turn around at the ends
        _delay_ms(30);
    }
}
