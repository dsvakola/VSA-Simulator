/*
  Relay Switching
  Switches a relay module on and off every two seconds.

  A relay is a switch worked by an electromagnet. With a relay module the
  small Arduino pin can switch a much larger load, such as a lamp or a
  fan (never connect mains voltage while learning!).
  The red light on the module shows when the relay is on.

  The circuit:
  - Relay module VCC -> 5V, GND -> GND
  - Relay module IN -> pin 7

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 29 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 06 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int relayPin = 7;

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(relayPin, HIGH);   // relay on
  Serial.println("Relay ON");
  delay(2000);

  digitalWrite(relayPin, LOW);    // relay off
  Serial.println("Relay OFF");
  delay(2000);
}
