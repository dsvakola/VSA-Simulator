<p align="center">
  <img src="assets/logo.png" alt="Vidyasagar Academy" width="140"/>
</p>

<h1 align="center">VSA Simulator</h1>

<p align="center">
  <b>Build circuits on a breadboard and run your own Arduino and MicroPython programs on them, completely offline.</b><br/>
  A free circuit and microcontroller simulator for Windows, made for school and college students.
</p>

<p align="center">
  <a href="https://vsa.edu.in/software/">Website</a> ·
  <a href="#example-programs">Examples</a> ·
  <a href="#how-to-load-your-program">How to load a program</a> ·
  <a href="LICENSE">Licence: GPL-3.0</a>
</p>

---

## What it does

VSA Simulator lets students build a circuit on a virtual breadboard, load the program they wrote in the
**Arduino IDE** or **Thonny**, and watch it run: LEDs glow, motors turn, displays show text, sensors respond,
and parts that get too much current get hot or burn out, just as they would on the bench.

- Works **fully offline**. No account, no internet, nothing is sent anywhere.
- Runs your **real compiled program**, not a simplified version of it.
- **MicroPython is built in** for the Pico W, ESP32 and ESP8266: nothing to flash or install.
- Live circuit simulation with warnings that teach: *"Add a resistor (220 Ω is a good start)"*, *"Short circuit!"*.
- Small and fast: a few MB to download, low memory use, tested for 30 minutes non-stop with no slowdown.

## Supported development boards

| Board | Program | Made with |
| --- | --- | --- |
| Arduino Uno R3 / Uno SMD | `.hex` | Arduino IDE |
| Arduino Nano | `.hex` | Arduino IDE |
| Raspberry Pi Pico W | `.py` (MicroPython) | Thonny |
| ESP32 DevKit (30 pins) | `.bin` (Arduino) or `.py` (MicroPython) | Arduino IDE or Thonny |
| ESP8266 NodeMCU | `.bin` (Arduino) or `.py` (MicroPython) | Arduino IDE or Thonny |

Wi-Fi and Bluetooth are not simulated.

## Parts you can use

| Group | Parts |
| --- | --- |
| Power | 9 V battery, 1.5 V AA cell, 3.7 V 18650 cell, 5 V USB power bank, variable DC supply (0–30 V, current limit 0.01–5 A, CV/CC) |
| Passive | Resistor, potentiometer, capacitor, diode |
| Inputs | Push buttons (4-leg and 2-leg), slide switch, SPST / SPDT / DPDT toggle switches, NTC thermistor, LDR |
| Lights | LED (red, green, blue, yellow, amber, white), RGB LED (common cathode), 2-leg colour-changing RGB LED |
| Displays | 7-segment FND500 (common cathode) and FND507 (common anode), LCD 16x2 with I2C backpack, OLED 0.96" SSD1306 |
| Sensors | Ultrasonic HC-SR04, DHT11, IR obstacle sensor, PIR motion sensor |
| Sound and motion | Active buzzer, servo SG90, DC motor (speed follows the voltage), relay module |
| Logic | NPN and PNP transistors, 74HC595 shift register |

Full, half, mini and double breadboards are available, or you can wire parts directly with no breadboard.

## How to load your program

**Arduino Uno or Nano:** in the Arduino IDE choose *Sketch → Export Compiled Binary*, then load the file ending in
`.ino.standard.hex` (not the one "with_bootloader").

**ESP32 DevKit:** choose the board *ESP32 Dev Module*, then *Sketch → Export Compiled Binary*, and load the file ending
in `.ino.bin`.

**ESP8266 NodeMCU:** choose the board *NodeMCU 1.0 (ESP-12E Module)*, then *Sketch → Export Compiled Binary*, and load
the file ending in `.ino.nodemcu.bin`.

**MicroPython (Pico W, ESP32, ESP8266):** write the program in Thonny, save it on *This computer* as a `.py` file, and
load that file. Libraries for the I2C LCD and the OLED are added by the simulator itself.

When you export or save again, the simulator reloads the program by itself.

## Example programs

Ready-made example programs, each with its circuit, are in the [`examples`](examples) folder, arranged by board.
Every example is tested in VSA Simulator and explained line by line for students. They are also available inside the
software from *File → Examples*.

## Download

VSA Simulator for Windows 10 and 11 will be available from the Microsoft Store and from
[vsa.edu.in/software](https://vsa.edu.in/software/).

## Developers

Developed by **Prof. Dattaraj S. Vidyasagar** and **Prof. Yash D. Vidyasagar** for
**Vidyasagar Academy**.

- Website: [vsa.edu.in](https://vsa.edu.in/)
- More of our software: [github.com/dsvakola/software](https://github.com/dsvakola/software)
- E-mail: softinquiry@vsa.edu.in

## Licence

VSA Simulator is free software under the [GNU General Public License v3.0](LICENSE). Third-party components keep
their own licences; see [NOTICE](NOTICE).

The example programs in this repository are in the public domain.

Arduino, Raspberry Pi and Espressif are trademarks of their respective owners. VSA Simulator is compatible with
their boards but is not made by or affiliated with them.
