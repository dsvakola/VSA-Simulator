/*
  Servo Sweep
  Sweeps a servo arm from 0 to 180 degrees and back.

  The circuit:
  - Servo GND (brown or black) -> GND
  - Servo V+ (red) -> +5 V
  - Servo SIGNAL (orange or yellow) -> PB2

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 24 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 01 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int servoPin = PIN_PB2;   // the signal wire is on PB2

// A servo wants a pulse every 20 ms. The pulse length sets the angle:
// 544 microseconds = 0 degrees, 2400 microseconds = 180 degrees.
void moveServo(int angle) {
  int pulse = map(angle, 0, 180, 544, 2400);
  for (int i = 0; i < 5; i++) {          // repeat so the arm has time to move
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulse);            // the pulse
    digitalWrite(servoPin, LOW);
    delay(20);                           // the rest of the 20 ms period
  }
}

void setup() {
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);   // open the serial port so the program can print messages
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 10) {   // 0 to 180 degrees
    Serial.print("Servo angle: ");                   // print a line in the Serial Monitor
    Serial.println(angle);
    moveServo(angle);
  }
  for (int angle = 180; angle >= 0; angle -= 10) {   // and back
    Serial.print("Servo angle: ");
    Serial.println(angle);
    moveServo(angle);
  }
}
