/*
 * LAB2.c
 *
 * Created: 1/27/2026 11:29:33 AM
 * Author : diego
 */ 
#define  F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU/16/BAUD)-1)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "ADC/ADC.h"
#include "LCD/LCD.h"
#include "UART/UART.h"

uint16_t valor1;
uint16_t valor2;
void setup(void);

int main(void)
{
    setup();
	char opc;
	//char operacion;
	char buffer2[32];
	uint8_t menu = 0;
	
	char buffer [6];
    while (1) 
    {
		
        cli();
        valor1 = adc3;
        valor2 = adc4;
        uint16_t v3 = (valor1 * 500UL)/63000;
        uint16_t v4 = (valor2 * 500UL)/63000;
		uint8_t d3 = v3 %100;
		uint8_t d4 = v4 %100;
        sei();
		
		if (!menu)
		{
			UART_TX_string("\r\n ---Menu---\r\n");
			UART_TX_string("1. Leer Potenciometros\r\n");
			UART_TX_string("2. Contador\r\n");
			menu = 1;
		}
		if(RX_dispo())
		{	
			opc = UART_RX_char();
			UART_TX_char(opc);
			UART_TX_string("\r\n");
			if (opc == '1')
			{
				snprintf(buffer2,sizeof(buffer2), "Valor voltaje 1: %u.",v3/100);
				UART_TX_string(buffer2);
				snprintf(buffer2,sizeof(buffer2), " %uV\r\n",d3);
				UART_TX_string(buffer2);
				snprintf(buffer2,sizeof(buffer2), "Valor voltaje 2: %u.",v4/100);
				UART_TX_string(buffer2);
				snprintf(buffer2,sizeof(buffer2), " %uV\r\n",d4);
				UART_TX_string(buffer2);


				menu =0;
				
			}
		}
		
        cursor_LCD(0,0);
        string_LCD("P1:");
        itoa(v3/100,buffer,10);
        string_LCD("     ");
        cursor_LCD(0,3);
        string_LCD(buffer);
        cursor_LCD(0,4);
        char_LCD('.');
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
	DDRD = 0b11111100; // PORTD2-7 COMO SALIDA DE DATOS
	DDRB = (1 << PB0) | (1 << PB1);// PORTB0-1 COMO SALIDA DE DATOS
	DDRC = (1 << PC0) | (1 << PC1)| (1 << PC2); // DECLARACION DE SALIDAS DE COMANDOS
	PORTC = 0x00;
	setup_LCD_8();
	init_ADC();
	UART_init(UBRR_VALUE);
	
	sei();
}