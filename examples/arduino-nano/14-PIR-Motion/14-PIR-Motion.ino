/*
  PIR Motion Alarm
  Lights an LED and prints a message when the PIR sensor sees movement.

  A PIR (passive infrared) sensor notices the heat of a moving person. Its
  OUT pin goes HIGH while it sees movement.
  In VSA Simulator, click the PIR sensor while simulating to make someone
  move in front of it.

  The circuit:
  - PIR VCC -> 5V, GND -> GND, OUT -> pin 2
  - LED: pin 13 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 10 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 20 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int pirPin = 2;
const int ledPin = 13;
int lastState = LOW;   // so we print only when something changes

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(pirPin);
  digitalWrite(ledPin, motion);   // LED follows the sensor

  if (motion != lastState) {
    if (motion == HIGH) {
      Serial.println("Motion detected!");
    } else {
      Serial.println("All quiet.");
    }
    lastState = motion;
  }
}
