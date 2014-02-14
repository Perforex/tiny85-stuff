/*
 * Generate a PWM square wave on an attiny85
 * 
 * 
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <my85libs.h>

uint16_t actualADC;
uint16_t actualMin = 10;
uint16_t actualMax = 255;
uint16_t actualDif;
uint16_t scaledADC;


int main()
{
	DDRB |= (1<<PB0);					// PWM port set to output

    initADC(PB3);
	
 	OCR0A = 128;						// 75% duty cycle
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
  }	
 }
