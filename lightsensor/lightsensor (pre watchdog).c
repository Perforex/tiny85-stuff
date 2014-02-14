/*
 * lightsensor.c
 * 
 * Copyright 2013 spb <spb@spb-desktop>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <stdio.h> 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include <serial85dbg.h>
#include <my85libs.h>

#define red PB2
#define blue PB0

char debugmsg[30];
uint8_t lightLevel;
uint16_t counter = 0;   // 930 counts = 30 secs
uint16_t secs30 = 930;
uint16_t secs15 = 465;
uint16_t secs10 = 310;

void initADC();
void delay_ms(uint16_t);
void initCounter();

int main( void ) 
{
  s85dbgBegin(19200);
  initADC();
  initCounter();
  DDRB |= (1<<red);
  DDRB |= (1<<blue);

  while(1)
  {
     ADCSRA |= (1 << ADSC);         // start ADC measurement
     while (ADCSRA & (1 << ADSC) ); // wait until conversion completes 

     lightLevel = ADCH;
//     sprintf(debugmsg,"ADCH is %i \n",lightLevel); 
//	 s85dbgWriteStr(debugmsg);	
//	 delay_ms(750);

	if(counter>=secs10)
	 {  	  
	 if(lightLevel > 245)
	  {
		 PORTB |= (1<<red);
		 delay_ms(250);
		 PORTB &= ~(1<<red);
		 PORTB |= (1<<blue);
		 delay_ms(250);
		 PORTB &= ~(1<<blue);
	  }
	 s85dbgWriteStr("Counter reset \n");
	 counter=0;
	 }
  }
}

void initCounter()
{
 TCCR0A |= (1 << WGM01);		// Configure timer 1 for CTC mode
 TIMSK |= (1 << OCIE0A);		// Enable CTC interrupt
 sei(); 				 		// Enable global interrupts
 
 OCR0A = 252; 			 		// Set CTC compare value 252
 
 TCCR0B |= (1 << CS00); 		// Set prescalar at 1024
 TCCR0B |= (0 << CS01); 
 TCCR0B |= (1 << CS02);	
}	

ISR(TIM0_COMPA_vect)
{
  counter++;
}
