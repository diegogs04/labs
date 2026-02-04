/*
 * Lab3.c
 *
 * Created: 2/3/2026 4:07:23 PM
 * Author : diego
 */ 
//Librerias
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "ADC/ADC.h"
#include "SPI/SPI.h"



//Variables
uint8_t valor1 = 0;
uint8_t valor2 = 0; 

//Function prototypes
void refreshPORT(uint8_t valor);
void setup();
//Main

int main(void)
{
	cli();
	setup();
	spiInit(SPI_SLAVE_SS, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	init_ADC();
	SPCR |= (1 << SPIE);
	sei();
	while (1)
	{
		ADCSRA |= (1 << ADSC);
		PORTD = adc3;
	}
}

//NON-Interrupt subroutines
void setup(){
	UCSR0B = 0x00;
	DDRC |= (1 << PORTC5);																								//SALIDA ESCLAVO
//	DDRB |= (1 << PORTB0) | (1 << PORTB1);																				//SALIDA LEDS
DDRD |= (1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);				//SALIDA LEDS
	
	PORTC &= ~(1 << PORTC5);
	PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
	PORTD &= ~((1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7));
}

void refreshPORT(uint8_t valor){
	if (valor & 0b10000000)
	{
		PORTB |= (1 << PORTB1);
		}else{
		PORTB &= ~(1 << PORTB1);
	}
	
	if (valor & 0b01000000)
	{
		PORTB |= (1 << PORTB0);
		}else{
		PORTB &= ~(1 << PORTB0);
	}
	
	if (valor & 0b00100000)
	{
		PORTD |= (1 << PORTD7);
		}else{
		PORTD &= ~(1 << PORTD7);
	}
	
	if (valor & 0b00010000)
	{
		PORTD |= (1 << PORTD6);
		}else{
		PORTD &= ~(1 << PORTD6);
	}
	
	if (valor & 0b00001000)
	{
		PORTD |= (1 << PORTD5);
		}else{
		PORTD &= ~(1 << PORTD5);
	}
	
	if (valor & 0b00000100)
	{
		PORTD |= (1 << PORTD4);
		}else{
		PORTD &= ~(1 << PORTD4);
	}
	
	if (valor & 0b00000010)
	{
		PORTD |= (1 << PORTD3);
		}else{
		PORTD &= ~(1 << PORTD3);
	}
	
	if (valor & 0b00000001)
	{
		PORTD |= (1 << PORTD2);
		}else{
		PORTD &= ~(1 << PORTD2);
	}
}

ISR(SPI_STC_vect)
{
	uint8_t spiValor = SPDR;
	if(spiValor == 'c')
	{
		valor1 = adc3;
		valor2 = adc4;
	if (spiValor == 'a')
	{
		spiWrite(valor1);
		_delay_ms(200);
	}
	else if (spiValor == 'b')
	{
		spiWrite(valor2);
		_delay_ms(200);
	}
	}
}
