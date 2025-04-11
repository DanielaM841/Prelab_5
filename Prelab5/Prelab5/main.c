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
#include "PWM_servo/PWM_servo.h"
/******** Variables***********/
uint8_t Valor_ADC = 0;
uint16_t DutyCycle;
/***************************/
// Function prototypes
void setup();
//void PWM1_init();
void ADC_init();
//void rest_servo();
//uint16_t Valor_Servo_PWM(uint8_t ADC_v);


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
	cli();
	// Configurar presclaer de sistema
	CLKPR	= (1 << CLKPCE);
	CLKPR	= (1 << CLKPS2); // 16 PRESCALER -> 1MHz
	DDRB |= (1 << DDB1); 
	UCSR0B = 0;
	PWM1_init(); 
	ADC_init();
	sei();
}
/*void PWM1_init()
{
	// Configurar Timer1 en modo Fast (no invertido)
	TCCR1A |= (1 << COM1A1); 
	TCCR1A |=( 1 << WGM11); 
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1 << CS11); //Fast mode 8 bits, prescaler de 8
	ICR1 = 2499; // Valor máximo para no exceder 20ms 
	
} */
void ADC_init()
{
	ADMUX =0;
	ADMUX |= (1<< REFS0); //REFERENCIA = VCC
	ADMUX |= (1<< ADLAR); // JUSTIFICACIÓN A LA IZQUIERDA
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1)); // Limpiar bits MUX
	ADMUX |=  (1<< MUX0); //HABILITAR EL ADC 1
	
	ADCSRA = 0;
	ADCSRA |= (1<< ADPS1) | (1<< ADPS0) | (1<< ADEN) | (1<< ADIE);
	ADCSRA |= (1<< ADSC);
}

//ISR 
ISR(ADC_vect){
	Valor_ADC = ADCH;
	//PORTD = ADCH;
	DutyCycle= Valor_Servo_PWM(Valor_ADC);
	rest_servo(DutyCycle); 
	_delay_ms(1);
	ADCSRA |= (1<<ADSC);
	
}
/*
//Funciones de las librerias 
uint16_t Valor_Servo_PWM(uint8_t ADC_v)
{
	return (ADC_v * 239UL / 255) + 69; 
}

void rest_servo(uint16_t duty)
{
	OCR1A = duty;	// Se actualiza el registro con el valor correcto. 
}
*/