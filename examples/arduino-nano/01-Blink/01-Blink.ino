/*
  Blinking LED Code
  Turns the built-in LED on the Arduino Nano development board on and off.

  Most Arduino boards like Uno, Nano and Mega have an on-board SMD LED
  internally connected to pin 13 (the MKR1000 uses pin 6).
  This example code blinks the built-in LED once every second. An external
  LED on pin 13 blinks together with it.

  The circuit:
  - External LED: pin 13 -> 220 ohm resistor -> LED anode (long leg)
  - LED cathode (short leg) -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 29 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 06 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

// LED_BUILTIN is the pin of the on-board LED: pin 13 on the Arduino Nano.
const int ledPin = LED_BUILTIN;

void setup() {
  // The pin starts as an input; make it an output so it can drive the LED.
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);   // open the serial port so the program can print messages
}

void loop() {
  digitalWrite(ledPin, HIGH);   // 5 V on the pin: the LED turns on
  Serial.println("LED on");     // print a line in the Serial Monitor
  delay(1000);                  // wait for one second (1000 milliseconds)
  digitalWrite(ledPin, LOW);    // 0 V on the pin: the LED turns off
  Serial.println("LED off");
  delay(1000);                  // wait for one second again
}
