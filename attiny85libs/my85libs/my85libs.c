/*
 * my85libs.c
 * 
 * Some functions that I use so regularly that they may as well be in one
 * place. See my85libs.h for full details.
 * 
 * Dec 2013
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
#include <util/delay.h>
#include <avr/interrupt.h>
#include "my85libs.h"

/* These functions initialise the ADC 
ADC Notes
	Clock   Available prescaler values
   ---------------------------------------
	 1 MHz   8 (125kHz), 16 (62.5kHz)
	 4 MHz   32 (125kHz), 64 (62.5kHz)
	 8 MHz   64 (125kHz), 128 (62.5kHz)
	16 MHz   128 (125kHz)
   below example set prescaler to 128 for mcu running at 8MHz
  */
void initADC(uint8_t _MYADC_)
{
  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set prescaler to 64, bit 2 
            (1 << ADPS1) |     // set prescaler to 64, bit 1 
            (0 << ADPS0);      // set prescaler to 64, bit 0  

if (_MYADC_ == PB2)
{
  ADMUX =  
            (1 << ADLAR) |     // left shift result
            (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
            (0 << MUX3)  |     // use ADC1 for input (PB2), MUX bit 3
            (0 << MUX2)  |     // use ADC1 for input (PB2), MUX bit 2
            (0 << MUX1)  |     // use ADC1 for input (PB2), MUX bit 1
            (1 << MUX0);       // use ADC1 for input (PB2), MUX bit 0
}            
if (_MYADC_ == PB3)
{
  ADMUX =            
            (1 << ADLAR) |     // left shift result
            (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
            (0 << MUX3)  |     // use ADC3 for input (PB3), MUX bit 3
            (0 << MUX2)  |     // use ADC3 for input (PB3), MUX bit 2
            (1 << MUX1)  |     // use ADC3 for input (PB3), MUX bit 1
            (1 << MUX0);       // use ADC3 for input (PB3), MUX bit 0
}            
if (_MYADC_ == PB4)
{
  ADMUX =            
            (1 << ADLAR) |     // left shift result
            (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
            (0 << MUX3)  |     // use ADC2 for input (PB4), MUX bit 3
            (0 << MUX2)  |     // use ADC2 for input (PB4), MUX bit 2
            (1 << MUX1)  |     // use ADC2 for input (PB4), MUX bit 1
            (0 << MUX0);       // use ADC2 for input (PB4), MUX bit 0
}            
}
uint8_t readADC()
{
     ADCSRA |= (1 << ADSC);         // start ADC measurement
     while (ADCSRA & (1 << ADSC) ); // wait until conversion completes 
	 return(ADCH);	
}	
void delay_ms(uint16_t delay)
{
	uint16_t k;
	for(k=0;k<delay;k++) _delay_ms(1);
}	
uint16_t encoder()
{
 static uint8_t state=0x03;					//Start with both pins high
 static uint8_t damper;						//Prevents over reporting
 static uint16_t encoder_value=0;			//The value
 static uint16_t max_encoder_value=255; 	//Maximum range
 static uint16_t precision=3;				//Increments per click

 state <<=2;								//Save previous state
 if(PINB & (1 << ACW)) state |=(1<<0);		//Port 1
 if(PINB & (1 << CW)) state |=(1<<1); 		//Port 2
 state &= 0x0f;								//Remove high order nibble
 if(damper)
  {if(state!=15) return(encoder_value); 	//Prevent over reporting
   else damper=0;}

 if(state==0x0e && encoder_value < (max_encoder_value - precision))
  {
   encoder_value += precision;
   damper=1;
  }
 if(state==0x0d && encoder_value > precision)
  {
   encoder_value -= precision;
   damper=1;   
  } 
 return(encoder_value); 
} 
