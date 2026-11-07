/*
  Timer 0 Delay
  Toggles an LED every 500 ms, timed by Timer 0 running by itself.

  Instead of waiting in a loop, Timer 0 counts in the background and
  raises an interrupt every 50 ms. The program counts 10 of them (500 ms)
  and then toggles the LED on P1.0. The main loop is free for other work.

  The circuit:
  - +5 V -> 220 ohm resistor -> LED anode, LED cathode -> P1.0

  You can modify this code and save it with another file name to simulate in
  VSA Simulator.

  Modified 03 November 2026 by Prof. Dattaraj S. Vidyasagar
  Modified 04 November 2026 by Prof. Yash D. Vidyasagar

  This example code is in the public domain.
  For a great collection of example codes to simulate on VSA Simulator,
  visit: https://github.com/dsvakola/VSA-Simulator
  Or visit our official website: https://vsa.edu.in/
  To check our collection of useful software, visit: https://github.com/dsvakola/software
*/

#ifdef __SDCC
#include <8052.h>      // SDCC
#else
#include <reg52.h>     // Keil
#endif

volatile unsigned char ticks = 0;   // counts 50 ms steps

// The interrupt routine of Timer 0 (interrupt number 1).
#ifdef __SDCC
void timer0_isr(void) __interrupt(1)
#else
void timer0_isr(void) interrupt 1
#endif
{
  TH0 = 0x4C;           // reload 65536 - 46080 = 0x4C00 (about 50 ms)
  TL0 = 0x00;
  ticks++;
}

void main(void) {
  TMOD = (TMOD & 0xF0) | 0x01;   // Timer 0, mode 1 (16-bit)
  TH0 = 0x4C;
  TL0 = 0x00;
  ET0 = 1;                       // allow the Timer 0 interrupt
  EA = 1;                        // allow interrupts
  TR0 = 1;                       // start the timer

  while (1) {
    if (ticks >= 10) {           // 10 x 50 ms = 500 ms
      ticks = 0;
      P1_0 = !P1_0;              // toggle the LED
    }
  }
}
