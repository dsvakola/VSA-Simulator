/*
  Push Button and LED
  Lights the LED while the push button is pressed.

  The button pin uses the Arduino Mega 2560's own pull-up resistor (INPUT_PULLUP),
  so no extra resistor is needed for the button. The pin reads HIGH when
  the button is released and LOW when it is pressed.
  In VSA Simulator, press and hold the button with the mouse while
  simulating.

  The circuit:
  - Push button: one side -> pin 2, other side -> GND
  - LED: pin 13 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 22 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 23 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int buttonPin = 2;    // the push button
const int ledPin = 13;      // the LED (also the built-in LED)
int lastState = HIGH;       // the last button state, so a message is printed only when it changes

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // HIGH when released, LOW when pressed
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);   // open the serial port so the program can print messages
}

void loop() {
  // Read the button. LOW means it is pressed (it connects the pin to GND).
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);   // pressed: LED on
  } else {
    digitalWrite(ledPin, LOW);    // released: LED off
  }

  if (buttonState != lastState) {   // the state changed: print it once
    Serial.println(buttonState == LOW ? "Button pressed: LED on" : "Button released: LED off");
    lastState = buttonState;
  }
}
