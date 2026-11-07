/*
  Serial Hello
  Sends a message and a counter to the Serial Monitor and echoes what you type.

  Open the Serial Monitor in VSA Simulator, type a letter and press
  Send: the program sends it back.

  The circuit: none needed (the Serial Monitor is built in).

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 16 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 25 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

int counter = 0;

void setup() {
  Serial.begin(9600);                       // start the serial port at 9600 baud
  Serial.println("Hello from the ATmega128!");
}

void loop() {
  if (Serial.available() > 0) {             // a character was typed
    char c = Serial.read();
    Serial.print("You typed: ");
    Serial.println(c);
  }

  Serial.print("Count: ");
  Serial.println(counter);
  counter++;
  delay(1000);
}
