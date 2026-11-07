/*
  LDR Night Light
  Switches an LED on when the room gets dark.

  The LDR (light dependent resistor) and a 10 k resistor form a voltage
  divider. In bright light the LDR has a low resistance and the ADC
  reads a high number; in the dark it reads a low number.
  Click the LDR while simulating to change the light.

  The circuit:
  - +5 V -> LDR -> PF0 -> 10 k resistor -> GND
  - PB0 -> 220 ohm resistor -> LED anode, LED cathode -> GND

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 05 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 19 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int ldrPin = A0;   // between the LDR and the 10 k resistor
const int ledPin = PIN_PB0;   // the LED
const int darkLevel = 300;  // below this reading we call it "dark"

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(ldrPin);   // high = bright, low = dark

  Serial.print("Light level: ");
  Serial.println(light);

  if (light < darkLevel) {
    digitalWrite(ledPin, HIGH);     // dark: switch the light on
  } else {
    digitalWrite(ledPin, LOW);      // bright: switch it off
  }
  delay(300);
}
