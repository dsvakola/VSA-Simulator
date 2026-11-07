/*
  Servo Sweep
  Sweeps a servo arm from 0 to 180 degrees and back.

  The circuit:
  - Servo GND (brown or black) -> GND
  - Servo V+ (red) -> +5 V
  - Servo SIGNAL (orange or yellow) -> PB1

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

#include <Servo.h>

Servo myServo;   // the servo object that controls one servo

void setup() {
  myServo.attach(PIN_PB1);   // the signal wire is on PB1
}

void loop() {
  // Turn from 0 to 180 degrees, one degree at a time.
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(15);   // give the arm time to get there
  }
  // And back again from 180 to 0.
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
