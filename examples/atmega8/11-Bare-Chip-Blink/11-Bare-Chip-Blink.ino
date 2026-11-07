/*
  Bare ATmega8 chip with crystal and reset
  Blinks an LED on PB0 of a bare ATmega8 chip wired on the breadboard, as on a real circuit board.

  How to wire a bare ATmega8:
  - Power: VCC (pin 7) and AVCC (pin 20) -> +5 V; GND (pins 8 and 22) -> GND
  - Crystal 16 MHz between XTAL1 (pin 9) and XTAL2 (pin 10), with a 22 pF
    capacitor from each to GND (the 3-leg crystal part has both capacitors built in)
  - Reset: RESET (pin 1) has a pull-up resistor inside; a push button from RESET to GND resets the chip
  - LED: PB0 (pin 14) -> 220 ohm resistor -> LED anode, LED cathode -> GND
  In the Arduino IDE choose MiniCore, ATmega8, Clock: 16 MHz external.
  The program is the same as 01-Blink.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 04 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 25 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int ledPin = PIN_PB0;   // the LED (PB0)

void setup() {
  pinMode(ledPin, OUTPUT);     // make the pin an output
}

void loop() {
  digitalWrite(ledPin, HIGH);  // LED on
  delay(1000);                 // wait one second
  digitalWrite(ledPin, LOW);   // LED off
  delay(1000);
}
