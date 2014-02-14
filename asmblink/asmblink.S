;-----------------------------------------------------------------------
; Simple interrupt driven LED blinker
; 
; 8Mhz = 8 * 1024 * 1024 per second
; 0.5 secs = 4 * 1024 * 1024
; Set prescaler to 1024  
; 0.5 secs = 4 * 1024 = 4096 interrupts
; CTC compare value = 128 (8 bit timer)
; Counter = 4096 / 128 = 32
;-----------------------------------------------------------------------
.NOLIST
.LIST
#include <avr/io.h>
#include <stdio.h> 
	rjmp	main							; On reset branch to main code
.global main
.func main
main:
		ldi	r16,1<<DDB0						; Load R16 for port PB1 out
		out	DDRB,r16 						; Write port settings
		ldi	r17,1<<PB0						; Load R17 for port PB1 high
		out PORTB,r17						; Set the port high
		nop
loop:
		rjmp loop							; Endless loop	
.data
	counter: .byte 0
