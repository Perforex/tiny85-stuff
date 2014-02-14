/*
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

//
// Defines
//
#define true 1
#define false 0
#define HIGH 1
#define LOW 0


//
// Includes
//
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "serial85dbg.h"
//
// Globals
//

uint16_t _tx_delay = 0;

// private static method for timing
static inline void tunedDelay(uint16_t delay);

//
// Lookup table
//
typedef struct _DELAY_TABLE {
        long baud;
        unsigned short tx_delay;
} DELAY_TABLE;

//8mHz
static const DELAY_TABLE table[] PROGMEM = 
{
  //  baud  tx
  { 115200,9,     }, //115200,   1,          5,         5,      3  ** Fails at this baud
  { 57600,17,     }, //57600,    1,          15,        15,     13 ** Fails at this baud
  { 38400,27,     }, //38400,    2,          25,        26,     23 ** Works but not 100% reliably
  { 31250,29,     },
  { 28800,32,     },
  { 19200,53,     }, //19200,    20,         55,        55,     52 ** Works reliably at 19200 and below
  { 14400,72,     },
  { 9600,112,     },
  { 4800,230,     },
  { 2400,469,     },
  { 1200,945,     },
  { 300,3802,     },
};

const int XMIT_START_ADJUSTMENT = 4;  //4

//
// Private methods
//

/* static */
inline void tunedDelay(uint16_t delay) {
        uint8_t tmp = 0;

        asm volatile("sbiw    %0, 0x01 \n\t"
                        "ldi %1, 0xFF \n\t"
                        "cpi %A0, 0xFF \n\t"
                        "cpc %B0, %1 \n\t"
                        "brne .-10 \n\t"
                        : "+w" (delay), "+a" (tmp)
                        : "0" (delay)
        );
}

//
// Public methods
//

void s85dbgBegin(long speed) {
        unsigned i;

        SERDDR |= (1<<TXPIN); // set TX for output
        SERPORT |= (1<<TXPIN); // assumes no inverse logic

        for (i = 0; i < sizeof(table) / sizeof(table[0]); ++i) {
                long baud = pgm_read_dword(&table[i].baud);
                if (baud == speed) {
                        _tx_delay = pgm_read_word(&table[i].tx_delay);
                        return;
                }
        }
}

size_t s85dbgWrite(uint8_t b) {
	
		byte mask; 
		
        if (_tx_delay == 0) return 0;   //setWriteError();        

        uint8_t oldSREG = SREG; 		// store interrupt flag
        cli();  						// turn off interrupts for a clean txmit

										// Write the start bit
        SERPORT &= ~(1<<TXPIN); 		// tx pin low
        tunedDelay(_tx_delay + XMIT_START_ADJUSTMENT);

        // Write each of the 8 bits
        for (mask = 0x01; mask; mask <<= 1) {
                if (b & mask) // choose bit
                        SERPORT |= (1<<TXPIN); // tx pin high, send 1
                else
                        SERPORT &= ~(1<<TXPIN); // tx pin low, send 0

                tunedDelay(_tx_delay);
        }
        SERPORT |= (1<<TXPIN); // tx pin high, restore pin to natural state
        SREG = oldSREG; // turn interrupts back on
        tunedDelay(_tx_delay);

        return 1;
}
void s85dbgWriteStr(char *SSmsg)
{
  while(*SSmsg) {
	s85dbgWrite((uint8_t)*SSmsg);
	SSmsg++;   
   }   
}	
