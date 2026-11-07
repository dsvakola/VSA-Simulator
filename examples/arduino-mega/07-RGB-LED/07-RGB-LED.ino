/*
  RGB LED Colours
  Mixes red, green and blue light in a common cathode RGB LED to make many colours.

  Each colour of the RGB LED has its own pin. With PWM (analogWrite) each
  can be set from 0 to 255, and mixing them makes other colours:
  red + green = yellow, green + blue = cyan, red + blue = magenta.

  The circuit:
  - Pin 9 -> 220 ohm -> R,  pin 10 -> 220 ohm -> G,  pin 11 -> 220 ohm -> B
  - Common cathode (longest leg, K) -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 11 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 30 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

// Sets the three colours at once (each 0 to 255).
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);   // open the serial port so the program can print messages
}

void loop() {
  Serial.println("Colour: red");
  setColor(255, 0, 0);     delay(1000);   // red
  Serial.println("Colour: green");
  setColor(0, 255, 0);     delay(1000);   // green
  Serial.println("Colour: blue");
  setColor(0, 0, 255);     delay(1000);   // blue
  Serial.println("Colour: yellow");
  setColor(255, 255, 0);   delay(1000);   // yellow
  Serial.println("Colour: cyan");
  setColor(0, 255, 255);   delay(1000);   // cyan
  Serial.println("Colour: magenta");
  setColor(255, 0, 255);   delay(1000);   // magenta
  Serial.println("Colour: white");
  setColor(255, 255, 255); delay(1000);   // white
}
