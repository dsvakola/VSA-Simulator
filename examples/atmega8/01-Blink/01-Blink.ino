/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.

  The circuit:
  - PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 24 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 22 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int ledPin = PIN_PB0;   // the LED (PB0)

void setup() {
  pinMode(ledPin, OUTPUT);     // make the pin an output
  Serial.begin(9600);          // open the serial port so the program can print messages
}

void loop() {
  digitalWrite(ledPin, HIGH);  // LED on
  Serial.println("LED on");    // print a line in the Serial Monitor
  delay(1000);                 // wait one second
  digitalWrite(ledPin, LOW);   // LED off
  Serial.println("LED off");
  delay(1000);
}
