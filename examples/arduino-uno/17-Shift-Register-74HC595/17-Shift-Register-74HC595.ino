/*
  8 LEDs with a 74HC595 Shift Register
  Lights 8 LEDs one after another, using only 3 Arduino pins and a 74HC595.

  The 74HC595 takes 8 bits one at a time on its data pin (DS), clocked in
  by SHCP. A pulse on STCP (the latch) then copies all 8 bits to the
  outputs Q0 to Q7 at once. shiftOut() sends the 8 bits for us.

  The circuit:
  - 74HC595 VCC and MR -> 5V; GND and OE -> GND
  - DS -> pin 11, STCP (latch) -> pin 8, SHCP (clock) -> pin 12
  - Q0 to Q7 -> 220 ohm resistor -> LED anode; each LED cathode -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 29 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 18 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int dataPin = 11;    // DS
const int latchPin = 8;    // STCP
const int clockPin = 12;   // SHCP

// Sends one byte to the 74HC595; each bit lights one LED.
void writeLeds(byte pattern) {
  digitalWrite(latchPin, LOW);                       // hold the outputs
  shiftOut(dataPin, clockPin, MSBFIRST, pattern);    // send the 8 bits
  digitalWrite(latchPin, HIGH);                      // show them all at once
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);   // open the serial port so the program can print messages
}

void loop() {
  // A light that runs from Q0 to Q7...
  for (int i = 0; i < 8; i++) {
    writeLeds(1 << i);
    Serial.print("LED Q");   // print which LED is on in the Serial Monitor
    Serial.print(i);
    Serial.println(" is on");
    delay(200);
  }
  // ...and back again.
  for (int i = 6; i > 0; i--) {
    writeLeds(1 << i);
    Serial.print("LED Q");   // print which LED is on in the Serial Monitor
    Serial.print(i);
    Serial.println(" is on");
    delay(200);
  }
}
