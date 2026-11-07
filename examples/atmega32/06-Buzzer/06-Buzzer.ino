/*
  Buzzer
  Beeps an active buzzer three times, then waits, and repeats.

  An active buzzer makes its tone by itself when it gets power, so
  the program only switches the pin on and off.

  The circuit:
  - PB0 -> buzzer + (long leg), buzzer - -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 24 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 26 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int buzzerPin = PIN_PB0;   // the buzzer (PB0)

// One beep of the given length, followed by the same length of silence.
void beep(int ms) {
  Serial.println("Beep!");   // print a line in the Serial Monitor
  digitalWrite(buzzerPin, HIGH);
  delay(ms);
  digitalWrite(buzzerPin, LOW);
  delay(ms);
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);   // open the serial port so the program can print messages
}

void loop() {
  for (int i = 0; i < 3; i++) {
    beep(150);          // three quick beeps ...
  }
  Serial.println("Pause");
  delay(1500);          // ... then a pause
}
