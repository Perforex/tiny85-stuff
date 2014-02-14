/*
serial85dbg  

A transmit only serial interface based on the original SoftwareSerial 
library. This library is specifically for Attiny85 and is intended for 
simple debugging. The only connection required is from PB1 to a serial 
Rx line on the PC. 

My intention is to try and keep the code as small as possible in order 
not to intrude on the program being debugged. 

SPB Dec 2013
 
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef serial85dbg_h
#define serial85dbg_h
//
// Types
//
typedef uint8_t bool;
typedef uint8_t byte;
//
// Hardcoded TX/RX 
//
#define SERDDR  DDRB		
#define SERPORT PORTB		
#define SERPIN  PINB
#define TXPIN   PB1			// This can be changed to whatever suits

//
// Definitions
//
#define _SS_MAX_RX_BUFF 64 // RX buffer size, must be (1<<n)
#define _SS_RX_BUFF_MASK (_SS_MAX_RX_BUFF-1)
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

//
// public methods
//
void s85dbgBegin(long speed);
size_t s85dbgWrite(uint8_t byte);
void s85dbgWriteStr(char []);

#endif
