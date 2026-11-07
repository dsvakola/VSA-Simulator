/*
  Servo Sweep
  Sweeps the arm of an SG90 servo motor from 0 to 180 degrees and back.

  A servo turns its arm to the angle it is told. The Servo library sends
  the control pulses on the signal pin.
  The Servo library comes with the Arduino IDE.

  The circuit:
  - Servo brown wire (GND) -> GND
  - Servo red wire (V+) -> 5V
  - Servo orange wire (SIG) -> pin 9

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 28 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 19 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#include <Servo.h>

Servo myServo;   // the servo object that controls one servo

void setup() {
  myServo.attach(9);   // the signal wire is on pin 9
  Serial.begin(9600);  // open the serial port so the program can print messages
}

void loop() {
  // Turn from 0 to 180 degrees, one degree at a time.
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    if (angle % 10 == 0) {   // print every 10 degrees
      Serial.print("Servo angle: ");
      Serial.println(angle);
    }
    delay(15);   // give the arm time to get there
  }
  // And back again from 180 to 0.
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    if (angle % 10 == 0) {   // print every 10 degrees
      Serial.print("Servo angle: ");
      Serial.println(angle);
    }
    delay(15);
  }
}
