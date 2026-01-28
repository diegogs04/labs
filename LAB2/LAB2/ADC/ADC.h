/*
 * ADC.h
 *
 * Created: 1/27/2026 4:38:05 PM
 *  Author: diego
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <util/delay.h>
void init_ADC(void);
ISR (ADC_vect);

#endif /* ADC_H_ */