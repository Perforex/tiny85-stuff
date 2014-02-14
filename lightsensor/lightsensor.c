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
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include <serial85dbg.h>
#include <my85libs.h>

#define RED PB3

//char debugmsg[30];
uint8_t lightLevel;

void initWatchdog();
void system_sleep();

int main( void ) 
{
//  s85dbgBegin(19200);
  initADC(PB2);
  initWatchdog();
  portOut(RED)

  while(1)
  {
	 system_sleep();				// System sleep for 8s 
     lightLevel = readADC();		// Read the light sensor

//   sprintf(debugmsg,"ADCH is %i \n",lightLevel); 
//	 s85dbgWriteStr(debugmsg);	

	 if(lightLevel > 245)
	  {
		 portHi(RED);
		 delay_ms(450);
		 portLo(RED);
	  }
  }
}

void initWatchdog()
{
	wdt_reset();
	WDTCR |= (1<<WDCE)|(1<<WDE);	// Enable watchdog
//	WDTCR |= (1<<WDP3)|(1<<WDP0);   // Prescaler 1024 or 8s
//	WDTCR |= (1<<WDP3);   			// Prescaler 512 or 4s
	WDTCR |= (1<<WDP2)|(1<<WDP1)|(1<<WDP0);   // Prescaler 256 or 2s
	WDTCR |= (1<<WDIE);				// Enable interrupt
	sei();							// Enable all interrupts
}	
void system_sleep() 
{
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
	sleep_enable();
	sleep_mode();                        // System sleeps 
	sleep_disable();                     // System continues execution here when watchdog times out 
}
ISR(WDT_vect) 
{
  // Not really required but included for completeness
}

