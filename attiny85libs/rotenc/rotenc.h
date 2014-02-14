 /*
 * rotenc.h
 * 
 *                +----+
 * NC          1 -|    |- 8 Vcc
 * NC          2 -|    |- 7 ENC CW
 * ENC Anti CW 3 -|    |- 6 NC
 * GND         4 -|    |- 5 NC 
 *                +----+
 * 
 * Connect pin 3 to the anti clockwise pin of the rotary encoder 
 * Connect pin 7 to the clockwise pin of the rotary encoder
 * 
 * Public Functions
 * 
 * void reInit(uint16_t max)	-	
 *   Setup the functions. Call once passing the max value (max 65535)
 *   Defaults to 256 if not specified
 * 
 * int  reRead()	-   Call to read the encoder value 
 * 						returns uint8_t between 0 - 255
 * 
 * eg:
 * 
 *  uint8_t volume;
 *   
 *  reInit(4000);
 * 
 *  while(;;)
 *   {
 *     volume = reRead();
 *   }
 * 
 * This library assumes that the encoder produces an out of phase signal
 * that leads according to the direction of rotation.
 */
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define reCWpin  PB2					// INT0 pin trigger do not change
#define reACWpin PB4					// PCINTO pin trigger can be changed

void reInit(uint16_t);
int reRead();

