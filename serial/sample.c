#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "serial85dbg.h"

// Timer timing for baud rates
//
#define OCR4800          52     // div 64
#define OCR9600          26     // div 64
#define OCR19200        104     // div 8
#define OCR38400         52     // div 8
#define OCR115200       138     // div 1

// incoming buffer
volatile char *inbuf[32];
// outgoing buffer
volatile char *outbuf[32];


void delay_ms(uint16_t);

char testPattern[30];
uint8_t i=0; 

int main()
{
 s85dbgBegin(19200);
 DDRB |= (1<<PB2);
 
 while (1) 
 {
	sprintf(testPattern,"Value of i is %i \n",i); 
	s85dbgWriteStr(testPattern);
	delay_ms(750);
	PORTB |= (1<<PB2);
	delay_ms(100);
	PORTB &= ~(1<<PB2);
	i++;
 }
}

void delay_ms(uint16_t delay)
{
	uint16_t k;
	for(k=0;k<delay;k++) _delay_ms(1);
}	
