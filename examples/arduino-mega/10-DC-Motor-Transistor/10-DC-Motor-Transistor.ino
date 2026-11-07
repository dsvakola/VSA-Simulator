/*
  DC Motor Speed Control
  Controls the speed of a DC motor with PWM through an NPN transistor.

  An Arduino pin can give only about 20 mA, far too little for a motor.
  The pin drives the base of an NPN transistor, and the transistor
  switches the motor's own 9 V battery. The diode across the motor
  protects the transistor from the motor's voltage spike.
  The motor speeds up, runs at full speed, slows down and stops.

  The circuit:
  - Pin 9 -> 1 k resistor -> transistor base (B)
  - Transistor emitter (E) -> GND
  - 9 V battery + -> motor terminal 1; motor terminal 2 -> transistor collector (C)
  - Diode across the motor: cathode (striped end) to battery +, anode to collector
  - 9 V battery - -> GND of the board (common ground)

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 27 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 07 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int motorPin = 9;   // PWM pin to the transistor's base

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Speed up from stop to full speed.
  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(motorPin, speed);
    delay(40);
  }
  Serial.println("Full speed");
  delay(2000);

  // Slow down to a stop.
  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(motorPin, speed);
    delay(40);
  }
  Serial.println("Stopped");
  delay(2000);
}
