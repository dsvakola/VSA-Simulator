"""
  DHT11 Temperature and Humidity
  Reads the temperature and humidity from a DHT11 sensor.

  MicroPython has the dht module built in, so no extra file is needed.
  In VSA Simulator, click the DHT11 and move the temperature and humidity
  sliders.

  The circuit:
  - DHT11 VCC -> 3V3
  - DHT11 DATA -> D5 (GPIO14)
  - DHT11 GND -> GND

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Modified 03 November 2026 by Prof. Dattaraj S. Vidyasagar
  Modified 04 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
"""

from machine import Pin
import dht
import time

sensor = dht.DHT11(Pin(14))

while True:
    time.sleep(2)   # the DHT11 can be read about once every 2 seconds
    try:
        sensor.measure()
    except OSError:
        print("Could not read the DHT11. Check the wiring.")
        continue
    print("Temperature:", sensor.temperature(), "C   Humidity:", sensor.humidity(), "%")
