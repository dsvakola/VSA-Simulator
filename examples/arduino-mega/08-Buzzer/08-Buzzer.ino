/*
  Active Buzzer Alarm
  Sounds an active buzzer in short beeps, like an alarm.

  An active buzzer has its own oscillator inside, so it beeps as soon as
  it gets power. The program only switches it on and off.
  Turn on the buzzer sound in File > Preferences to hear it.

  The circuit:
  - Buzzer + (longer leg) -> pin 8
  - Buzzer - -> GND

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

const int buzzerPin = 8;

// One beep of the given length, followed by the same length of silence.
void beep(int ms) {
  digitalWrite(buzzerPin, HIGH);
  delay(ms);
  digitalWrite(buzzerPin, LOW);
  delay(ms);
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Three quick beeps...
  for (int i = 0; i < 3; i++) {
    beep(150);
  }
  // ...then a pause.
  delay(1000);
}
