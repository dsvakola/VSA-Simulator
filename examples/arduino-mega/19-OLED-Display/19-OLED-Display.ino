/*
  OLED Display (SSD1306)
  Draws text, a frame and a moving ball on a 0.96 inch 128x64 OLED display.

  This example needs the "Adafruit SSD1306" and "Adafruit GFX" libraries.
  In the Arduino IDE open Sketch > Include Library > Manage Libraries,
  search for "Adafruit SSD1306" and install it (accept "Adafruit GFX"
  when asked).
  The I2C address is usually 0x3C (sometimes 0x3D). In VSA Simulator,
  select the OLED and choose the same address in the Inspector.

  The circuit:
  - OLED GND -> GND, VCC -> 5V
  - OLED SDA -> pin 20 (SDA), SCL -> pin 21 (SCL)

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

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 128 x 64 pixels, on the I2C bus (Wire), no reset pin (-1).
Adafruit_SSD1306 display(128, 64, &Wire, -1);

int ballX = 10;   // where the ball is
int stepX = 3;    // how far it moves each time

void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC: the display makes its own high voltage inside.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found. Check the wiring and the address.");
    while (true) { }   // stop here
  }
}

void loop() {
  display.clearDisplay();

  display.setTextSize(2);                 // twice the normal size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 4);
  display.print("VSA Sim");

  display.drawRect(0, 28, 128, 36, SSD1306_WHITE);   // a frame
  display.fillCircle(ballX, 46, 6, SSD1306_WHITE);   // the ball

  display.display();   // nothing shows until this is called

  // Move the ball and bounce it off the sides of the frame.
  ballX = ballX + stepX;
  if (ballX < 8 || ballX > 119) {
    stepX = -stepX;
  }
  delay(20);
}
