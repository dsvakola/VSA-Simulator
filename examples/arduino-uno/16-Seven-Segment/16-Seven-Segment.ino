/*
  7-Segment Counter (FND500)
  Counts from 0 to 9 on a common cathode 7-segment display.

  The FND500 has 7 segments (a to g) and a decimal point. In a common
  cathode display all the LED cathodes are joined to COM, which goes to
  GND. Setting a segment pin HIGH lights that segment.
  For simplicity one 330 ohm resistor sits in the COM line; a resistor on
  every segment pin keeps the brightness even.

  The circuit:
  - Segments a, b, c, d, e, f, g -> pins 2, 3, 4, 5, 6, 7, 8
  - Decimal point DP -> pin 9
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
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int dpPin = 9;

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
  pinMode(dpPin, OUTPUT);
}

void loop() {
  for (int n = 0; n <= 9; n++) {
    showDigit(n);
    digitalWrite(dpPin, n % 2);   // the dot blinks with every count
    delay(1000);
  }
}
