/*
  Potentiometer to Serial Monitor
  Reads a potentiometer (0 to 1023) and prints the value and the voltage.

  Turn the knob while simulating: click the potentiometer to open its
  slider. The chip's analog-to-digital converter (ADC) turns 0 to 5 V
  into the numbers 0 to 1023.

  The circuit:
  - Potentiometer: left leg -> +5 V, right leg -> GND, middle (wiper) -> PA0

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 03 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 07 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int potPin = A0;   // the wiper (PA0)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(potPin);            // 0 to 1023
  float volts = value * 5.0 / 1023.0;        // convert to volts

  Serial.print("Value: ");
  Serial.print(value);
  Serial.print("   Voltage: ");
  Serial.print(volts);
  Serial.println(" V");
  delay(500);
}
