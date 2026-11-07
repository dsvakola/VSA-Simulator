/*
  7-Segment Display (FND500)
  Counts from 0 to 9 on a common-cathode 7-segment display.

  The common pin (COM) goes to GND through one 330 ohm resistor and a
  HIGH on a segment pin lights that segment.

  The circuit:
  - PD2 -> segment A, PD3 -> segment B, PD4 -> segment C, PD5 -> segment D, PD6 -> segment E, PD7 -> segment F, PB0 -> segment G
  - COM -> 330 ohm resistor -> GND

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

// Pins for segments a, b, c, d, e, f, g, in that order.
const int segmentPins[7] = {PIN_PD2, PIN_PD3, PIN_PD4, PIN_PD5, PIN_PD6, PIN_PD7, PIN_PB0};

// Which segments are lit for each digit (1 = on), in the order a..g.
const byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},   // 0
  {0, 1, 1, 0, 0, 0, 0},   // 1
  {1, 1, 0, 1, 1, 0, 1},   // 2
  {1, 1, 1, 1, 0, 0, 1},   // 3
  {0, 1, 1, 0, 0, 1, 1},   // 4
  {1, 0, 1, 1, 0, 1, 1},   // 5
  {1, 0, 1, 1, 1, 1, 1},   // 6
  {1, 1, 1, 0, 0, 0, 0},   // 7
  {1, 1, 1, 1, 1, 1, 1},   // 8
  {1, 1, 1, 1, 0, 1, 1},   // 9
};

// Shows one digit (0 to 9) on the display.
void showDigit(int n) {
  for (int s = 0; s < 7; s++) {
    digitalWrite(segmentPins[s], digits[n][s] ? HIGH : LOW);
  }
}

void setup() {
  for (int s = 0; s < 7; s++) {
    pinMode(segmentPins[s], OUTPUT);
  }
}

void loop() {
  for (int n = 0; n <= 9; n++) {
    showDigit(n);
    delay(1000);
  }
}
