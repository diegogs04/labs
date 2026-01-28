/*
 * LCD.c
 *
 * Created: 1/27/2026 11:58:03 AM
 *  Author: diego
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
static void enable_LCD(void)
{
	PORTC |= (1 << PC2);   // EN = 1
	_delay_us(1);
	PORTC &= ~(1 << PC2);  // EN = 0
	_delay_us(100);
}
void setup_LCD_8()
{
	_delay_ms(20);
	command_LCD(0x38);    // 8 bits, 2 líneas, 5x8
	command_LCD(0x0C);    // Display ON, cursor OFF
	command_LCD(0x06);    // Incremento automático
	clear_LCD();
}
void command_LCD(uint8_t com)
{
	PORTD = com;
	PORTC &= ~(1 << PC0);
	PORTC &= ~(1 << PC1);
	enable_LCD();
	_delay_ms(2);
}
void char_LCD(uint8_t car)
{
	 PORTD = car;           // Datos
	 PORTC |= (1 << PC0);   // RS = 1
	 PORTC &= ~(1 << PC1);  // RW = 0
	 enable_LCD();
	 _delay_us(100);
}
void string_LCD(char *cad)
{
	while (*cad)
	{
		char_LCD(*cad++);
	}
}
void cursor_LCD(uint8_t fil, uint8_t col)
{
	uint8_t pos;
	if (fil == 0)
	pos = 0x80 + col;
	else
	pos = 0xC0 + col;
	command_LCD(pos);
}
void clear_LCD()
{
	command_LCD(0x01);
	_delay_ms(2);
}