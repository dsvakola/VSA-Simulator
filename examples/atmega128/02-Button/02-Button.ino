/*
  Push Button and LED
  Lights the LED while the push button is pressed.

  The button pin uses the chip's own pull-up resistor (INPUT_PULLUP),
  so no extra resistor is needed for the button. The pin reads HIGH
  when the button is released and LOW when it is pressed.
  In VSA Simulator, press and hold the button with the mouse.

  The circuit:
  - Push button: one side -> PC0, other side -> GND
  - LED: PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

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

const int buttonPin = PIN_PC0;   // the push button (PC0)
const int ledPin = PIN_PB0;      // the LED (PB0)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // HIGH when released, LOW when pressed
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // LOW means the button is pressed (it connects the pin to GND).
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH);   // pressed: LED on
  } else {
    digitalWrite(ledPin, LOW);    // released: LED off
  }
}
