/*
  Fading LED
  Makes an LED slowly brighten and dim using PWM (analogWrite).

  analogWrite() switches the pin on and off very fast. The longer it stays
  on in each cycle, the brighter the LED looks. The value goes from 0
  (always off) to 255 (always on).
  On the Mega 2560 the PWM pins are 2 to 13 and 44 to 46.

  The circuit:
  - Pin 9 -> 220 ohm resistor -> LED anode (long leg)
  - LED cathode (short leg) -> GND

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

const int ledPin = 9;     // a PWM pin (marked ~ on the board)
int brightness = 0;       // how bright the LED is now (0 to 255)
int fadeAmount = 5;       // how much to change it each time

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  analogWrite(ledPin, brightness);   // set the brightness

  // Change the brightness for the next time round the loop.
  brightness = brightness + fadeAmount;

  // At either end, turn round and fade the other way.
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(30);   // a short wait so the fading can be seen
}
