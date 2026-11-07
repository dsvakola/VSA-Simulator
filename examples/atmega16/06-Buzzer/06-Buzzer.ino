/*
  Buzzer
  Beeps an active buzzer three times, then waits, and repeats.

  An active buzzer makes its tone by itself when it gets power, so
  the program only switches the pin on and off.

  The circuit:
  - PB0 -> buzzer + (long leg), buzzer - -> GND

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

const int buzzerPin = PIN_PB0;   // the buzzer (PB0)

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
  for (int i = 0; i < 3; i++) {
    beep(150);          // three quick beeps ...
  }
  delay(1500);          // ... then a pause
}
