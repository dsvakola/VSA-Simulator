/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.

  The circuit:
  - PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

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

const int ledPin = PIN_PB0;   // the LED (PB0)

void setup() {
  pinMode(ledPin, OUTPUT);     // make the pin an output
}

void loop() {
  digitalWrite(ledPin, HIGH);  // LED on
  delay(1000);                 // wait one second
  digitalWrite(ledPin, LOW);   // LED off
  delay(1000);
}
