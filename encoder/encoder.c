/*
 * Testing a Rotary Encoder on an Attiny85.
 * 
 *                +----+
 * NC          1 -|    |- 8 NC
 * BLUE LED    2 -|    |- 7 ENC CW
 * ENC Anti CW 3 -|    |- 6 NC
 * GND         4 -|    |- 5 RED LED 
 *                +----+
 * 
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <my85libs.h>


int main()
{
	DDRB |= (1<<PB0);					// PWM port set to output
	
 	OCR0A = 128;						// 50% duty cycle
	TCCR0A |= (1<<COM0A1);				// Fast PWM non inverting mode
	TCCR0A |= (1<<WGM00);				// Top OCRA
	TCCR0A |= (1<<WGM01);				// Update at Bottom
//	TCCR0B |= (1<<WGM02);				// TOV set at top
//	TCCR0B |= (1<<CS00);				// No Prescaler
	TCCR0B |= (1<<CS01);				// /8 Prescaler
//	TCCR0B |= (1<<CS02);				// /256 Prescaler

	sei(); 
 
 while (1) 
 {
    OCR0A=encoder();	 
  }	
 }
