/*
  Servo Sweep (AVR Studio style, plain C)
  Sweeps a servo arm from 0 to 180 degrees and back.

  AVR chips such as the ATmega8 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 07, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 07-Servo-Sweep. A servo wants a pulse every 20 ms;
  the pulse length sets the angle (1000 us = 0 degrees, 2000 us = 180
  degrees). Here the pulses are made by the program itself.

  The circuit:
  - Servo GND (brown or black) -> GND
  - Servo V+ (red) -> +5 V
  - Servo SIGNAL (orange or yellow) -> PB2

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

// _delay_us() needs a fixed number, so a longer wait is made of 10 us pieces.
static void delay_us_var(uint16_t us)
{
    while (us >= 10)
    {
        _delay_us(10);
        us -= 10;
    }
}

// Moves the servo to an angle (0 to 180) by sending 5 pulses.
static void move_servo(uint8_t angle)
{
    uint16_t pulse = 1000 + (uint16_t)angle * 1000 / 180;   // pulse length in microseconds

    for (uint8_t i = 0; i < 5; i++)
    {
        PORTB |= (1 << PB2);     // pulse high
        delay_us_var(pulse);
        PORTB &= ~(1 << PB2);    // pulse low
        _delay_ms(20);                          // the rest of the 20 ms period
    }
}

int main(void)
{
    DDRB |= (1 << PB2);          // servo signal pin = output

    while (1)
    {
        for (int16_t angle = 0; angle <= 180; angle += 10)      // 0 to 180 degrees
            move_servo(angle);
        for (int16_t angle = 180; angle >= 0; angle -= 10)      // and back
            move_servo(angle);
    }
}
