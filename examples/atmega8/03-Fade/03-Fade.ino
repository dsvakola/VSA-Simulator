/*
  Fade
  Fades an LED smoothly up and down with PWM (analogWrite).

  Only some pins can do PWM (pulse width modulation). PB1 is one of them.
  The LED gets brighter as the pulses get longer.

  The circuit:
  - PB1 -> 220 ohm resistor -> LED anode, LED cathode -> GND

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

const int ledPin = PIN_PB1;   // a PWM pin (PB1)
int brightness = 0;         // how bright the LED is (0 to 255)
int step = 5;               // how much to change each time

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  analogWrite(ledPin, brightness);   // set the brightness
  brightness = brightness + step;

  // Turn around at the ends: 0 is off, 255 is fully on.
  if (brightness <= 0 || brightness >= 255) {
    step = -step;
  }
  delay(30);
}
