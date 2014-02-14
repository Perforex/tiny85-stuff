/*
 * bedlight.c
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
 */
#include <stdio.h> 
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include <serial85dbg.h>
#include <my85libs.h>

#define SWITCH PB3

char debugmsg[30];
uint8_t lightLevel;
uint8_t flags = 0;

#define DARK 			0b00000001			// 1
#define LIGHT_OFF		0b00000010			// 2
#define	AUTO_ON			0b00000100			// 4
#define BUTTON			0b00001000			// 8

/*
 * Switch Logic
 * 
 * Flags = 7   It's dark, light is off and has not been on - Switch the light on (and flag initial switch on)
 * Flags = 8   It's light, light is on and button pressed - Switch the light off 
 * Flags = 9   It's dark, light is on and button pressed - Switch the light off
 * Flags = 10  It's light, light is off and button pressed - Switch the light on
 * Flags = 11  It's dark, light is off, has been on, button pressed - Switch the light on
 * 
*/ 

uint8_t button_pressed();

int main( void ) 
{
  s85dbgBegin(19200);
  initADC(PB2);
  portOut(SWITCH);
  
  while(1)
  {
     lightLevel = readADC();										// Read the light sensor
	 if(lightLevel > 245) flags |= (1<<DARK);						// Flag if it's dark
	 if(!(PORTB & (1 << SWITCH))) flags |= (1<<LIGHT_OFF);			// Flag if the light is off
	 if(button_pressed()) flags |= (1<<BUTTON);						// Flag the button press
	 
	 switch(flags)
	 {
		 case 7:
			portHi(SWITCH);
			flags |= (1<<AUTO_ON);
			break;
		 case 8:
			portLo(SWITCH);
			break;
		 case 9:
			portLo(SWITCH);
			break;
		 case 10:
			portHi(SWITCH);
			break;
		 case 11:
			portHi(SWITCH);
			break; 	
     }  	  
	 sprintf(debugmsg,"ADCH is %i \n",lightLevel); 
	 s85dbgWriteStr(debugmsg);	
  }
}
uint8_t button_pressed()
{
	return 0;
}	
