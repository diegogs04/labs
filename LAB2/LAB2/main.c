/*
 * LAB2.c
 *
 * Created: 1/27/2026 11:29:33 AM
 * Author : diego
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC/ADC.h"
#include "LCD/LCD.h"

uint16_t valor1;
uint16_t valor2;
void setup(void);

int main(void)
{
    setup();

	
	char buffer [6];
    while (1) 
    {
		valor1 = adc3;
		valor2 = adc4;
		clear_LCD();
		
		string_LCD(valor1);
    }
}

void setup()
{
	cli();
	UCSR0B = 0x00; // DESHABILITACION DE COMUNICACION SERIAL
	DDRD = 0xFF; // PORTD COMO SALIDA DE DATOS
	DDRC = (1 << PC0) | (1 << PC1)| (1 << PC2); // DECLARACION DE SALIDAS DE COMANDOS
	setup_LCD_8();
	init_ADC();
	
	sei();
}