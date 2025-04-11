/*
 * PWM_servo.h
 *
 * Created: 11/04/2025 14:11:01
 *  Author: Lenovo
 */ 


#ifndef PWM_SERVO_H_
#define PWM_SERVO_H_

void PWM1_init();
void rest_servo();
uint16_t Valor_Servo_PWM(uint8_t ADC_v);



#endif /* PWM_SERVO_H_ */