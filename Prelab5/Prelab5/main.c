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
#include "PWM_T0/PWM_T0.h"
/******** Variables***********/
uint8_t Valor_ADC = 0;
uint8_t Valor_ADC2 = 0;
uint8_t led_pmw = 0;
uint16_t DutyCycle=0;
uint8_t Contador_Mux=0;
uint8_t Contador_T0=0;
uint8_t ValorPMW_T0=0;
uint16_t DutyCycle_LED=0;
/***************************/
// Function prototypes
void setup();
void ADC_init();
void rest_servo2(uint16_t duty);
uint16_t Valor_Servo_PWM2(uint8_t ADC_v);
void Mux_pines();

int main(void)
{
	setup();
    while (1) 
    {
		_delay_ms(1);
    }
}

//NON_Interrupt subroutines 
void setup()
{
	cli();
	// Configurar presclaer de sistema
	CLKPR	= (1 << CLKPCE);
	CLKPR	= (1 << CLKPS2); // 16 PRESCALER -> 1MHz
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3); //configurar los camales A y b del timer 1 como salida 
	//PORTB |= (1 << PORTB3); 
	UCSR0B = 0;
	PWM1_init();  
	ADC_init();
	initT0L();
	ADCSRA	|= (1 << ADSC);	
	sei();
}
void ADC_init()
{
	ADMUX =0;
	ADMUX |= (1<< REFS0); //REFERENCIA = VCC
	ADMUX |= (1<< ADLAR); // JUSTIFICACIÓN A LA IZQUIERDA
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1)); // Limpiar bits MUX 
	
	ADCSRA = 0;
	ADCSRA |= (1<< ADPS1) | (1<< ADPS0) | (1<< ADEN) | (1<< ADIE);
}

void Mux_pines()
{
	//Contador_Mux++;
	switch(Contador_Mux)
	{
		case 0: 
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1)|(1<< MUX0)); // Limpiar bits MUX
		ADMUX |=  (1<< MUX0); //HABILITAR EL ADC 1
		Valor_ADC = ADCH;
		DutyCycle= Valor_Servo_PWM(Valor_ADC);
		rest_servo(DutyCycle);
		break;
		
		case 1:
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1)|(1<< MUX0)); // Limpiar bits MUX
		ADMUX |=  (1<< MUX1); //HABILITAR EL ADC 2
		led_pmw= ADCH;
		DutyCycle_LED=ValorPMW_T0_F(led_pmw);
		break;
		
		case 2:
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1)|(1<< MUX0)); // Limpiar bits MUX
		ADMUX |=  (1<< MUX2) ; //HABILITAR EL ADC 3
		Valor_ADC2 = ADCH;
		DutyCycle= Valor_Servo_PWM2(Valor_ADC2);
		rest_servo2(DutyCycle);
		break;
		default:
		break;
		}
		Contador_Mux++;
		if(Contador_Mux==3){
		Contador_Mux=0; 
		}
		
}

//ISR 
ISR(ADC_vect){
	Mux_pines();
	ADCSRA |= (1<<ADSC);
	
}
ISR(TIMER0_OVF_vect)
{
	Contador_T0++;						//Sumar el contador del timer
	if (Contador_T0<DutyCycle_LED){ //comparar con el dutycicle del mapeo del led
		PORTB |= (1<<PORTB3);
	}
	else if (Contador_T0>=DutyCycle_LED){
		PORTB &= ~(1<<PORTB3);
	}
	if (Contador_T0 >= 20)
	{
		Contador_T0 = 0;
	}									// Se hace un if para evitar parpadeo, se cambio a 20 para que no se viera
	TCNT0	= 251;						
}

//Funciones de las librerias 
uint16_t Valor_Servo_PWM2(uint8_t ADC_v2)
{
	return (ADC_v2 * 239UL / 255) + 69; 
}

void rest_servo2(uint16_t duty)
{
	OCR1B = duty;	
}
