/*
  Thermometer with an NTC Thermistor
  Measures temperature with a 10 k NTC thermistor and prints it in degrees Celsius.

  An NTC thermistor's resistance falls as it gets warmer. With a 10 k
  resistor it forms a voltage divider on A0. The program works out the
  thermistor's resistance and turns it into a temperature with the Beta
  formula (Beta = 3950 for this thermistor).
  In VSA Simulator, click the thermistor while simulating and heat it.

  The circuit:
  - Thermistor: one leg -> 5V, other leg -> A0
  - 10 k resistor: A0 -> GND

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 17 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 30 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int thermistorPin = A0;
const float seriesResistor = 10000.0;   // the fixed 10 k resistor
const float nominalResistance = 10000.0; // thermistor resistance at 25 C
const float nominalTemp = 25.0;          // that temperature, in C
const float beta = 3950.0;               // the thermistor's Beta value

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(thermistorPin);

  // The thermistor is at the top of the divider:
  // R_thermistor = R_series * (1023 / reading - 1)
  float resistance = seriesResistor * (1023.0 / reading - 1.0);

  // Beta formula: 1/T = 1/T0 + (1/B) * ln(R/R0), with T in kelvin.
  float kelvin = 1.0 / (1.0 / (nominalTemp + 273.15) + log(resistance / nominalResistance) / beta);
  float celsius = kelvin - 273.15;

  Serial.print("Temperature: ");
  Serial.print(celsius, 1);
  Serial.println(" C");

  delay(1000);
}
