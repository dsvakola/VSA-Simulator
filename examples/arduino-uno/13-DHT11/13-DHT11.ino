/*
  DHT11 Temperature and Humidity
  Reads temperature and humidity from a DHT11 sensor every two seconds.

  This example needs the "DHT sensor library" by Adafruit. In the Arduino
  IDE open Sketch > Include Library > Manage Libraries, search for
  "DHT sensor library" and install it (also accept "Adafruit Unified
  Sensor" when asked).
  In VSA Simulator, click the DHT11 while simulating to change the air.

  The circuit:
  - DHT11 VCC -> 5V, GND -> GND
  - DHT11 DATA -> pin 2

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 13 October 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 18 October 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#include <DHT.h>

#define DHTPIN 2        // the DATA pin
#define DHTTYPE DHT11   // the sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);   // the DHT11 can be read about once every 2 seconds

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();   // in Celsius

  // isnan() is true if the reading failed (for example, a loose wire).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Could not read the DHT11. Check the wiring.");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature, 0);
  Serial.print(" C   Humidity: ");
  Serial.print(humidity, 0);
  Serial.println(" %");
}
