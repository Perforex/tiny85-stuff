/*
 * rotenc.c
 * 
 * Rotary Encoder library for the Attiny85.
 * 
 * Copyright 2014 spb <spb@spb-desktop>
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
#include "rotenc.h"

volatile uint16_t enCounter=0;			// Counter value 
volatile uint8_t enFirst=1;  			// Interrupt triggered first flag	
volatile uint8_t enDown=1;	  			// For the pin interrupt because
										// we don't know which way it's 
										// going. down = 1, up = 0
uint16_t enCounterMax=0;

void reInit(uint16_t reMAX)
{
	
 if(reMAX) enCounterMax=reMAX;
 else enCounterMax = 256;
 	
 DDRB &= ~(1<<reCWpin);
// PORTB |= (1<<reCWpin);
 
 DDRB &= ~(1<<reACWpin);
// PORTB |= (1<<reACWpin);
 
 MCUCR |= (1<<ISC01);					// Trigger on falling edge  
 GIMSK |= (1<<PCIE);					// Pin change interrupt enabled
 GIMSK |= (1<<INT0);					// Pin0 interrupt enabled
 PCMSK |= (1<<PCINT4);					// Detect change on int 4
 sei();									// Enable interrupts
}	
int reRead()
{
	return(enCounter);
}	
ISR(INT0_vect) 
{
  if(enFirst)
   {	
    if(enCounter < (enCounterMax-1)) enCounter++;
    enFirst=0;
   }
  else
   {
	enFirst=1;   
   }	   
}	

ISR(PCINT0_vect) 
{
  if(enDown)
   {
	enDown=0;
	   
	if(enFirst)
	 {   	
      if(enCounter > 0) enCounter--;
      enFirst=0;
	 }
	 else 
	 {
	  enFirst=1;	 
     }	 
   }
  else
   {
	enDown=1;   
   }	   
}	
	


