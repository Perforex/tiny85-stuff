/*
 * my85libs.c - Attiny85 only
 * 
 * Some functions that I use so regularly that they may as well be in one
 * place.
 * 
 * Dec 2013
 * 
 * portOut(port)	- Open a port for output eg portOut(PB1)
 * portIn(port)		- Open a port for digital input eg portIn(PB1)
 * portHi(port)		- Set the port high eg portHi(PB1)
 * portLo(port)		- Set the port low eg portLow(PB1)
 * portTgl(port)	- Toggle port between low and high portTgl(PB1)
 * 
 * initADC()		- Initialise an ADC for reading. Declare MYADC as 
 * 					  the ADC port required. eg #define MYADC PB2
 * 					  (Defaults to PB2 if not defined)
 * 
 * readADC			- Read the previously initialised ADC - Returns an
 * 					  8 bit unsigned value from the ADC 
 * 					  eg volts = readADC();
 * 
 * delay_ms()		- Delays for a number of milliseconds up to 65,535 
 * 
 * encoder()		- Reads a rotory encoder connected between PB3 and PB4 
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
// Macro functions
#define portOut(__PIN) DDRB |= (1 << __PIN);
#define portIn(__PIN) DDRB &= ~(1 << __PIN);
#define portHi(__PIN) PORTB |= (1 << __PIN);
#define portLo(__PIN) PORTB &= ~(1 << __PIN);
#define portTgl(__PIN) PORTB ^= (1 << __PIN);
#
#define CW	PB4
#define ACW PB3
// Private Functions
//
// Public functions
//
uint8_t readADC();
void initADC(uint8_t);
void delay_ms(uint16_t);
uint16_t encoder();

