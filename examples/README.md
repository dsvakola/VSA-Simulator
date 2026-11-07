# Example programs for VSA Simulator

Each example has its own folder with the program and a ready-made VSA Simulator circuit (`.vsasim`).
The Arduino, 8051 and ATmega folders also hold the compiled `.hex` file.
Open the `.vsasim` file in VSA Simulator and press **Simulate** (F5).

| Folder | Board | Language |
| --- | --- | --- |
| `arduino-uno` | Arduino Uno R3 / Uno SMD | Arduino (C++) |
| `arduino-nano` | Arduino Nano | Arduino (C++) |
| `arduino-mega` | Arduino Mega 2560 | Arduino (C++) |
| `pico-w` | Raspberry Pi Pico W | MicroPython |
| `esp32` | ESP32 DevKit | MicroPython |
| `esp8266` | ESP8266 NodeMCU | MicroPython |
| `8051` | 8051 / 8052 development board (AT89S52) and a bare chip | C (Keil µVision or SDCC) |
| `atmega8` | ATmega8 development board and a bare chip | Arduino (C++) with MiniCore, and plain C (AVR Studio 4/6) |
| `atmega16` | ATmega16/32 development board (chip set to ATmega16) and a bare chip | Arduino (C++) with MightyCore, and plain C (AVR Studio 4/6) |
| `atmega32` | ATmega16/32 development board (chip set to ATmega32) and a bare chip | Arduino (C++) with MightyCore, and plain C (AVR Studio 4/6) |
| `atmega128` | ATmega128 development board and a bare chip | Arduino (C++) with MegaCore, and plain C (AVR Studio 4/6) |

All example programs are in the public domain. You can modify them and save them under another name to simulate in
VSA Simulator.

## The 19 examples on every board

01 Blink, 02 Push button and LED, 03 Fading LED, 04 Potentiometer, 05 LDR night light, 06 Thermistor thermometer,
07 RGB LED colours, 08 Buzzer, 09 Servo sweep, 10 DC motor with a transistor, 11 Relay, 12 Ultrasonic distance (HC-SR04),
13 DHT11 temperature and humidity, 14 PIR motion alarm, 15 IR obstacle sensor, 16 Seven-segment counter (FND500),
17 74HC595 LED chaser, 18 I2C LCD 16x2, 19 OLED display (SSD1306).

## The examples for the 8051 and ATmega chips

8051: 01 Blink, 02 Push button and LED, 03 Running LEDs, 04 Timer 0 delay, 05 Serial hello, 06 Seven-segment counter
(FND507), 07 LCD 16x2 (4-bit), 08 Buzzer, 09 DC motor with a transistor, 10 Relay, 11 External interrupt INT0 counter,
12 Bare chip with crystal and reset.

ATmega8, ATmega16, ATmega32 and ATmega128: 01 Blink, 02 Push button and LED, 03 Fade, 04 Potentiometer, 05 LDR night
light, 06 Buzzer, 07 Servo sweep, 08 Seven-segment counter (FND500), 09 I2C LCD 16x2, 10 Serial hello, 11 Bare chip with
crystal and reset (Arduino IDE style).

The same eleven programs are also written in plain C for AVR Studio 4/6 (Microchip Studio) with avr-gcc, as examples
12 to 22 (`12-Blink-C` ... `22-Bare-Chip-Blink-C`). They use the same circuits, so a teacher can show that one chip,
the heart of the Arduino boards, can be programmed in both styles.

The 8051 pins can pull a line LOW strongly but can push it HIGH only weakly, so the 8051 examples connect LEDs, the
buzzer and the motor transistor between +5 V and the pin: a LOW pin switches them on, as on real 8051 boards.

The 8051 programs compile with both Keil µVision and SDCC. In the Arduino IDE, install MiniCore, MightyCore or MegaCore
and choose the chip and **Clock: 16 MHz external**.

All of these examples also come with the software: **File → Examples**.

MicroPython examples need no extra files in VSA Simulator: the simulator adds the LCD and OLED drivers itself.
