/*
 * UART.c
 *
 * Created: 2/2/2026 11:49:38 AM
 *  Author: diego
 */ 
#define F_CPU 16000000UL
#include "UART.h"

void UART_init(uint16_t ubrr)
{
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr);
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
}

void UART_TX_char(char dato_s)
{
	while (!(UCSR0A &(1 << UDRE0)));
	UDR0 = dato_s;
}

void UART_TX_string(const char *str)
{
	while (*str)
	{
		UART_TX_char(*str++);
	}
}

char UART_RX_char(void)
{
	while (!(UCSR0A &(1 << RXC0)));
	return UDR0;
}
uint8_t RX_dispo(void)
{
	return (UCSR0A & (1 << RXC0));
}
