/*
  IR Obstacle Sensor
  Lights an LED when the IR sensor finds an object in front of it.

  The IR obstacle sensor sends out infrared light and watches for it to
  bounce back. Its OUT pin goes LOW when an object is near (within the
  range set on the module), and HIGH when the way is clear.
  In VSA Simulator, click the sensor while simulating and move the object.

  The circuit:
  - IR sensor VCC -> 5V, GND -> GND, OUT -> pin 2
  - LED: pin 13 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 20 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 24 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int irPin = 2;
const int ledPin = 13;
int lastState = HIGH;

void setup() {
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int clear = digitalRead(irPin);   // LOW = object found

  if (clear == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  if (clear != lastState) {
    Serial.println(clear == LOW ? "Obstacle ahead!" : "The way is clear.");
    lastState = clear;
  }
}
