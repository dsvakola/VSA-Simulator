/*
  LDR Night Light
  Turns an LED on when it gets dark, using an LDR (light-dependent resistor).

  The LDR and a 10 k resistor form a voltage divider. In bright light the
  LDR's resistance is low and A0 reads a high value; in the dark its
  resistance rises and A0 reads a low value.
  In VSA Simulator, click the LDR while simulating and change the light.

  The circuit:
  - LDR: one leg -> 5V, other leg -> A0
  - 10 k resistor: A0 -> GND
  - LED: pin 13 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 13 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 28 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int ldrPin = A0;
const int ledPin = 13;
const int darkLevel = 300;   // below this reading we call it "dark"

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(ldrPin);   // high = bright, low = dark

  Serial.print("Light level: ");
  Serial.println(light);

  if (light < darkLevel) {
    digitalWrite(ledPin, HIGH);   // dark: switch the light on
  } else {
    digitalWrite(ledPin, LOW);    // bright: switch it off
  }

  delay(300);
}
