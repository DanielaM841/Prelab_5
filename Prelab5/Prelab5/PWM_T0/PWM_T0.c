/*
 * PWM_T0.c
 *
 * Created: 24/04/2025 01:06:05
 *  Author: Lenovo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initT0L() // PWM0 manual usando timer0
{
	TIMSK0 |= (1<<TOIE0);
	TCCR0A	|= 0;
	TCCR0B	|= (1 << CS01); // Prescaler = 8
	TCNT0	= 251;
}
uint8_t ValorPMW_T0_F(uint8_t valordelADC){
	return (valordelADC * 50UL) / 255;
}