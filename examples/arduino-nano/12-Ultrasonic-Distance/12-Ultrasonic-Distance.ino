/*
  Ultrasonic Distance Meter
  Measures distance with an HC-SR04 ultrasonic sensor and prints it in centimetres.

  The sensor sends a short burst of sound when TRIG gets a 10 microsecond
  pulse. ECHO then stays HIGH for as long as the sound takes to reach the
  object and come back. Sound travels about 0.034 cm per microsecond, and
  the time covers the distance twice, so: distance = time x 0.034 / 2.
  In VSA Simulator, click the sensor while simulating and move the object.

  The circuit:
  - HC-SR04 VCC -> 5V, GND -> GND
  - HC-SR04 TRIG -> pin 9, ECHO -> pin 10

  The program also prints messages in the Serial Monitor, to show how a program can print text.

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Written on 25 September 2026 by Prof. Dattaraj S. Vidyasagar
  Modified on 05 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Make sure TRIG starts LOW, then send a 10 microsecond pulse.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // How long does ECHO stay HIGH? (in microseconds)
  long duration = pulseIn(echoPin, HIGH);

  // Turn the time into a distance in centimetres.
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance, 1);
  Serial.println(" cm");

  delay(500);
}
