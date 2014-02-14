/*
 * Testing a Rotary Encoder on an Attiny85.
 * 
 *                +----+
 * NC          1 -|    |- 8 NC
 * BLUE LED    2 -|    |- 7 ENC CW
 * ENC Anti CW 3 -|    |- 6 NC
 * GND         4 -|    |- 5 RED LED 
 *                +----+
 * 
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <serial85dbg.h>
#include <rotenc.h>

#define RED	PB0
#define BLUE PB3

char debugmsg[30];

void delay_ms(uint16_t);

uint16_t encoder_value; 

int main()
{
 //s85dbgBegin(19200);
 reInit(256);
 
 while (1) 
 {
	encoder_value = reRead();
//	sprintf(debugmsg,"v=%i\n",encoder_value); 
//	s85dbgWriteStr(debugmsg);
//	delay_ms(20);
  }	
 }
void delay_ms(uint16_t delay)
{
	uint16_t k;
	for(k=0;k<delay;k++) _delay_ms(1);
}	
