/*
 * PWM_servo.c
 *
 * Created: 11/04/2025 14:11:27
 *  Author: Lenovo
 */ 
//Funciones de las librerias
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void PWM1_init()
{
	// Configurar Timer1 en modo Fast (no invertido)
	TCCR1A |= (1 << COM1A1)|(1<<COM1B1);;
	TCCR1A |=( 1 << WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1 << CS11); //Fast mode 8 bits, prescaler de 8
	ICR1 = 2499; // Valor máximo para no exceder 2ms
	
}
uint16_t Valor_Servo_PWM(uint8_t ADC_v)
{
	return (ADC_v * 239UL / 255) + 69;
}

void rest_servo(uint16_t duty)
{
	OCR1A = duty;	// Se actualiza el registro con el valor correcto.
}