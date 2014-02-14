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
#include <rotenc.h>


#define CW	PB3
#define ACW PB4

void delay_ms(uint16_t);
void encoder();

static uint16_t encoder_value=0;
static uint16_t max_encoder_value=255; 
uint16_t precision=1;
uint16_t detents=20;
static uint8_t first=1;
static uint8_t cwTriggered=0;
static uint8_t acwTriggered=0;

int main()
{
	DDRB |= (1<<PB0);					// PWM port set to output
	
 	OCR0A = 128;						// 75% duty cycle
	TCCR0A |= (1<<COM0A1);				// Fast PWM non inverting mode
	TCCR0A |= (1<<WGM00);				// Top OCRA
	TCCR0A |= (1<<WGM01);				// Update at Bottom
//	TCCR0B |= (1<<WGM02);				// TOV set at top
//	TCCR0B |= (1<<CS00);				// No Prescaler
	TCCR0B |= (1<<CS01);				// /8 Prescaler
//	TCCR0B |= (1<<CS02);				// /256 Prescaler
	reInit(256);

	sei(); 
  	
  	precision = max_encoder_value/detents;
 
 while (1) 
 {
    encoder();	 
    OCR0A=encoder_value;
  }	
 }
void delay_ms(uint16_t delay)
{
	uint16_t k;
	for(k=0;k<delay;k++) _delay_ms(1);
}	
void encoder()
{
 
 if((PINB & (1 << CW)) && (PINB & (1 << ACW)))
  {
    if(cwTriggered && encoder_value < (max_encoder_value - precision))
     {
		 encoder_value += precision;
		 first=1;
		 cwTriggered=0;
     } 	 
    if(acwTriggered && encoder_value > (0+precision))
     {
		 encoder_value -= precision;
		 first=1;
		 acwTriggered=0;
     } 
     return;	 
   }
 
 if(!(PINB & (1 << CW)))
  {
   if(first) cwTriggered=1;
  }	  

 if(!(PINB & (1 << ACW)))
  {
   if(first) acwTriggered=1;
  }
}
