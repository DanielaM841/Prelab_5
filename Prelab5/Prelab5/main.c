/*
 * Prelab5.c
 *
 * Created: 11/04/2025 06:54:46
 * Author : Lenovo
 *Descripción: Pro
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/******** Variables***********/
uint16_t Valor_ADC = 0;
/***************************/
// Function prototypes
void setup();
void PWM1_init();

int main(void)
{
	setup();
    /* Replace with your application code */
    while (1) 
    {
    }
}

//NON_Interrupt subroutines 
void setup()
{
	cli()
	DDRB |= (1 << PORTB1);
	UCSR0B = 0;
	PWM1_init(); 
}
void PWM1_init()
{
	
} 
//ISR 