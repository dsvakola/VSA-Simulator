# Example programs for VSA Simulator

Each example has its own folder with the program and a ready-made VSA Simulator circuit (`.vsasim`).
The Arduino folders also hold the compiled `.hex` file.
Open the `.vsasim` file in VSA Simulator and press **Simulate** (F5).

| Folder | Board | Language |
| --- | --- | --- |
| `arduino-uno` | Arduino Uno R3 / Uno SMD | Arduino (C++) |
| `arduino-nano` | Arduino Nano | Arduino (C++) |
| `arduino-mega` | Arduino Mega 2560 | Arduino (C++) |
| `pico-w` | Raspberry Pi Pico W | MicroPython |
| `esp32` | ESP32 DevKit | MicroPython |
| `esp8266` | ESP8266 NodeMCU | MicroPython |

All example programs are in the public domain. You can modify them and save them under another name to simulate in
VSA Simulator.

## The 19 examples on every board

01 Blink, 02 Push button and LED, 03 Fading LED, 04 Potentiometer, 05 LDR night light, 06 Thermistor thermometer,
07 RGB LED colours, 08 Buzzer, 09 Servo sweep, 10 DC motor with a transistor, 11 Relay, 12 Ultrasonic distance (HC-SR04),
13 DHT11 temperature and humidity, 14 PIR motion alarm, 15 IR obstacle sensor, 16 Seven-segment counter (FND500),
17 74HC595 LED chaser, 18 I2C LCD 16x2, 19 OLED display (SSD1306).

MicroPython examples need no extra files in VSA Simulator: the simulator adds the LCD and OLED drivers itself.
