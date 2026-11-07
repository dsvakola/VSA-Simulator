/*
  I2C LCD 16x2 (AVR Studio style, plain C)
  Shows a message and a seconds counter on a 16x2 LCD with an I2C backpack.

  AVR chips such as the ATmega8 are the heart of the Arduino boards, so one chip can be programmed in two styles:
  Arduino IDE style (see example 09, the same circuit) or plain C with AVR Studio 4/6 (Microchip Studio), as here.

  Same program as 09-I2C-LCD. The LCD backpack (a PCF8574 chip) is
  controlled with two wires, SDA and SCL. The program uses the chip's
  TWI (I2C) hardware directly. Choose the I2C address (0x27 or 0x3F) in
  the Inspector so that it matches LCD_ADDRESS below.

  The circuit:
  - LCD GND -> GND, LCD VCC -> +5 V
  - LCD SDA -> PC4, LCD SCL -> PC5

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
#include <stdlib.h>

#define LCD_ADDRESS 0x27            // the I2C address of the backpack

// Bits of the backpack: P0 = RS, P1 = RW, P2 = E, P3 = backlight, P4..P7 = D4..D7.
#define BACKLIGHT 0x08
#define ENABLE    0x04
#define RS        0x01

// ---- TWI (I2C) master ------------------------------------------------------
static void twi_init(void)
{
    TWSR = 0;                       // prescaler 1
    TWBR = 72;                      // 100 kHz at 16 MHz
}

static void twi_start(uint8_t address)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);    // send START
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR = address << 1;                                  // address + write bit (0)
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

static void twi_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

static void twi_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);    // send STOP
}

// ---- LCD ------------------------------------------------------------------
// Sends 4 bits and pulses the E line so the LCD reads them.
static void send_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data = (nibble << 4) | BACKLIGHT | mode;
    twi_start(LCD_ADDRESS);
    twi_write(data | ENABLE);
    twi_write(data & ~ENABLE);
    twi_stop();
    _delay_us(100);
}

static void send_byte(uint8_t value, uint8_t mode)
{
    send_nibble(value >> 4, mode);          // high half first
    send_nibble(value & 0x0F, mode);        // then the low half
}

static void lcd_command(uint8_t c) { send_byte(c, 0); }
static void lcd_char(char c)       { send_byte(c, RS); }

static void lcd_print(const char *text)
{
    while (*text)
        lcd_char(*text++);
}

static void lcd_init(void)
{
    _delay_ms(50);
    send_nibble(0x03, 0);                   // the start-up sequence from the LCD data sheet
    _delay_ms(5);
    send_nibble(0x03, 0);
    send_nibble(0x03, 0);
    send_nibble(0x02, 0);                   // switch to 4-bit mode
    lcd_command(0x28);                      // 4-bit, 2 lines
    lcd_command(0x0C);                      // display on, cursor off
    lcd_command(0x06);                      // cursor moves right
    lcd_command(0x01);                      // clear the screen
    _delay_ms(3);
}

int main(void)
{
    char text[8];
    uint16_t seconds = 0;

    twi_init();
    lcd_init();
    lcd_command(0x80);                      // first line, first column
    lcd_print("VSA Simulator");

    while (1)
    {
        lcd_command(0xC0);                  // second line, first column
        lcd_print("Seconds: ");
        itoa(seconds, text, 10);            // number -> text
        lcd_print(text);
        _delay_ms(1000);
        seconds++;
    }
}
