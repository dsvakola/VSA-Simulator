/*
  Active Buzzer Alarm
  Sounds an active buzzer in short beeps, like an alarm.

  An active buzzer has its own oscillator inside, so it beeps as soon as
  it gets power. The program only switches it on and off.
  Turn on the buzzer sound in File > Preferences to hear it.

  The circuit:
  - Buzzer + (longer leg) -> pin 8
  - Buzzer - -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 06 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 20 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int buzzerPin = 8;

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
  // Three quick beeps...
  for (int i = 0; i < 3; i++) {
    beep(150);
  }
  // ...then a pause.
  Serial.println("Pause");
  delay(1000);
}
