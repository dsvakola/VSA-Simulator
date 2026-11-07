/*
  I2C LCD 16x2 Display
  Writes text and a running seconds counter on a 16x2 LCD with an I2C backpack.

  This example needs the "LiquidCrystal I2C" library by Frank de Brabander.
  In the Arduino IDE open Sketch > Include Library > Manage Libraries,
  search for "LiquidCrystal I2C" and install it.
  The I2C address is usually 0x27 (sometimes 0x3F). In VSA Simulator,
  select the LCD and choose the same address in the Inspector.

  The circuit:
  - LCD GND -> GND, VCC -> 5V
  - LCD SDA -> pin 20 (SDA), SCL -> pin 21 (SCL)

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 02 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 29 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Address 0x27, 16 characters, 2 lines.
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastSeconds = 9999;   // the last value that was printed

void setup() {
  Serial.begin(9600);   // open the serial port so the program can print messages
  lcd.init();        // start the LCD
  lcd.backlight();   // switch on the backlight

  lcd.setCursor(0, 0);   // column 0, line 0 (the top line)
  lcd.print("VSA Simulator");
  lcd.setCursor(0, 1);   // column 0, line 1 (the bottom line)
  lcd.print("Seconds: ");
}

void loop() {
  unsigned long seconds = millis() / 1000;   // seconds since the program started
  lcd.setCursor(9, 1);           // just after "Seconds: "
  lcd.print(seconds);
  if (seconds != lastSeconds) {  // print the seconds once, when they change
    Serial.print("Seconds: ");
    Serial.println(seconds);
    lastSeconds = seconds;
  }
  delay(200);
}
