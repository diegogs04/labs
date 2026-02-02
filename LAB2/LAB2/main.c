/*
 * LAB2.c
 *
 * Created: 1/27/2026 11:29:33 AM
 * Author : diego
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
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
        cli();
		valor1 = adc3;
		valor2 = adc4;
		uint16_t v3 = (valor1 * 500UL)/63000;
		uint16_t v4 = (valor2 * 500UL)/63000;
		sei();
		cursor_LCD(0,0);
		string_LCD("P1:");
		itoa(v3/100,buffer,10);
		string_LCD("     ");
		cursor_LCD(0,3);
		string_LCD(buffer);
		cursor_LCD(0,4);
		char_LCD('.');
		uint8_t d3 = v3 %100;
		string_LCD("     ");
		cursor_LCD(0,5);
		itoa(d3,buffer,10);
		string_LCD(buffer);
		string_LCD("     ");
		cursor_LCD(0,7);
		char_LCD('V');
		
		cursor_LCD(1,0);
		string_LCD("P2:");
		itoa(v4/100, buffer,10);
		string_LCD("     ");
		cursor_LCD(1,3);
		string_LCD(buffer);
		cursor_LCD(1,4);
		char_LCD('.');
		uint8_t d4 = v4 %100;
		string_LCD("     ");
		cursor_LCD(1,5);
		itoa(d4,buffer,10);
		string_LCD(buffer);
		string_LCD("     ");
		cursor_LCD(1,7);
		char_LCD('V');

		_delay_ms(300);
	

    }
}

void setup()
{
	cli();
	UCSR0B = 0x00; // DESHABILITACION DE COMUNICACION SERIAL
	DDRD = 0xFF; // PORTD COMO SALIDA DE DATOS
	DDRC = (1 << PC0) | (1 << PC1)| (1 << PC2); // DECLARACION DE SALIDAS DE COMANDOS
	PORTC = 0x00;
	setup_LCD_8();
	init_ADC();
	
	sei();
}