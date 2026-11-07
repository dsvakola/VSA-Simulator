/*
  Reading a Potentiometer
  Reads a potentiometer on A0 and prints the value and voltage to the Serial Monitor.

  analogRead() turns the voltage on an analog pin into a number from 0
  (0 V) to 1023 (5 V).
  In VSA Simulator, click the potentiometer while simulating and move the
  slider. Watch the numbers change in the Serial Monitor.

  The circuit:
  - Potentiometer end 1 -> 5V, end 2 -> GND
  - Potentiometer middle pin (wiper) -> A0

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 25 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 26 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int potPin = A0;

void setup() {
  // Start the serial connection at 9600 bits per second.
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(potPin);           // 0 to 1023
  float voltage = value * (5.0 / 1023.0);   // turn it back into volts

  Serial.print("Value: ");
  Serial.print(value);
  Serial.print("   Voltage: ");
  Serial.print(voltage, 2);                 // 2 digits after the point
  Serial.println(" V");

  delay(500);   // print twice a second
}
