/*
  I2C LCD 16x2
  Shows a message and a seconds counter on a 16x2 LCD with an I2C backpack.

  The LCD backpack (a PCF8574 chip) is controlled with only two wires,
  SDA and SCL, using the Wire library. The program below talks to the
  backpack directly, so no extra library has to be installed.
  Choose the I2C address (0x27 or 0x3F) in the Inspector so that it
  matches the address in the program.

  The circuit:
  - LCD GND -> GND, LCD VCC -> +5 V
  - LCD SDA -> PC4, LCD SCL -> PC5

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 09 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 06 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#include <Wire.h>

const byte lcdAddress = 0x27;   // the I2C address of the backpack

// Bits of the backpack: P0 = RS, P1 = RW, P2 = E, P3 = backlight, P4..P7 = D4..D7.
const byte BACKLIGHT = 0x08;
const byte ENABLE = 0x04;
const byte RS = 0x01;

// Sends one half byte (4 bits) and pulses the E line so the LCD reads it.
void sendNibble(byte nibble, byte mode) {
  byte data = (nibble << 4) | BACKLIGHT | mode;
  Wire.beginTransmission(lcdAddress);
  Wire.write(data | ENABLE);
  Wire.write(data & ~ENABLE);
  Wire.endTransmission();
  delayMicroseconds(100);
}

void sendByte(byte value, byte mode) {
  sendNibble(value >> 4, mode);     // high half first
  sendNibble(value & 0x0F, mode);   // then the low half
}

void lcdCommand(byte c) { sendByte(c, 0); }
void lcdChar(char c)    { sendByte(c, RS); }

void lcdPrint(const char *text) {
  while (*text) lcdChar(*text++);
}

void lcdInit() {
  delay(50);
  sendNibble(0x03, 0);   // the start-up sequence from the LCD data sheet
  delay(5);
  sendNibble(0x03, 0);
  sendNibble(0x03, 0);
  sendNibble(0x02, 0);   // switch to 4-bit mode
  lcdCommand(0x28);      // 4-bit, 2 lines
  lcdCommand(0x0C);      // display on, cursor off
  lcdCommand(0x06);      // cursor moves right
  lcdCommand(0x01);      // clear the screen
  delay(3);
}

void setup() {
  Serial.begin(9600);   // open the serial port so the program can print messages
  Wire.begin();
  lcdInit();
  lcdCommand(0x80);              // first line, first column
  lcdPrint("VSA Simulator");
}

void loop() {
  lcdCommand(0xC0);              // second line, first column
  lcdPrint("Seconds: ");
  lcdPrint(String(millis() / 1000).c_str());
  Serial.print("Seconds: ");           // print the same number in the Serial Monitor
  Serial.println(millis() / 1000);
  delay(1000);
}
