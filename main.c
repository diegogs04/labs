/*
 * LAB1.c
 *
 * Created: 1/19/2026 8:26:00 PM
 * Author : diego
 */ 
//ENCABEZADO
#define F_CPU 4000000
#include <avr/io.h> 
#include <avr/interrupt.h> // se incluyen interrupciones
#include "7seg/7seg.h" // se incluye libreria de funciones 7 segmentos

volatile uint8_t jug1 = 0; // contador jugador 1
volatile uint8_t jug2 = 0; // contador jugador 2
volatile uint8_t vic = 0; // bandera de victoria
volatile uint8_t run = 0; // bandera de habilitacion de carrera
volatile uint8_t cont = 0; // contador de overflows
volatile uint8_t seg = 0; // contador de segundos
volatile uint8_t aj2 = 1; // valor anterior de boton jugador 2
volatile uint8_t aj1 = 1; // valor anterior de boton jugador 1

//declaracion de funciones en main
void setup(); 
void timer_ini(void);


void setup ()
{
	cli();
	UCSR0B = 0x00; // DESHABILITACION DE COMUNICACION SERIAL
	DDRC &= ~(1 << PC4) | (1<< PC5);
	DDRC |= 0b00001111; // DECLARACION DE SALIDAS LEDS1
	DDRB |= 0b00001111; // DECLARACION SALIDAS LEDS2 
	DDRB &= ~(1 << PB4);// ENTRADA BOTONES
	PORTC |= (1 << PC4) | (1 << PC5);
	PORTB |= (1 << PB4); // PULLUPS BOTONES
	
	PCICR |= (1 << PCIE1) | (1 << PCIE0); // HABLITIACION DE INTERRUPCIONES
	PCMSK0 |= (1 << PCINT4); 
	PCMSK1 |= (1 << PCINT12) | (1 << PCINT13);
	seg_init(); // llamado para la configuracion del 7 segmentos
	timer_ini(); 
	
	sei();
	
}
void timer_ini()
{
	TCCR0A = 0;
	TCCR0B = (1 << CS00) | (1 << CS02); // PRESCALER 1024
	TIMSK0 = (1 << TOIE0); // ENCENDER TOV0 SI HAY OVERFLOW
}
int main(void)
{
    setup(); // configuracion
    while (1) 
    {
		if (run) // ver si la bandera de inicio de la bandera es true
		{
			seg_write(seg);// actualizar display 
		}
		else if (vic == 1) // revisar si jugador 1 gano 
		{
			seg_write(4); // escribir 1 en el display
			PORTC |= 0b00001111;   // encender todas las luces del jugador
		}
		else if (vic == 2) // revisar si jugador 2 gano 
		{
			seg_write(3); // escribir 2 en el display
			PORTB |= 0b00001111;   // encender todas las luces del jugador    
		}
		else
		{
			seg_off(); // apagar display al terminar conteo 
		}
		PORTC = (PORTC & 0b00110000) | jug1; // Actualizar leds sin afectar pullups
		PORTB = (PORTB & 0b00110000) | jug2;
    }
}

//RUTINAS DE INTERRUPCIONES
ISR(TIMER0_OVF_vect)
{
	if (run) // si se activa la bandera de carrera habilitar contadores de decadas
	{
		cont ++;  // aumentar el contador de overflows
		if (cont >= 30)
		{
			cont = 0; // resetear valor de overflows
			seg ++; // aumentar contador de segundos 
			if (seg == 6) // si contador de segundos llega a 6
			{
				seg = 0; // reseteo de segundos
				run = 0; // reseteo de bandera de carrera
			}
		}
	}
}

ISR (PCINT1_vect)
{
	if (!(PINC & (1 << PC5))) // Inicio de secuencia
	{
		jug1 = 0; // reseteo de contador jugador 1
		jug2 = 0; // reseteo de contador jugador 2
		run = 1; // habilita contador
		seg=0; // resetea segundos por si acaso
		vic= 0; // resetea valor de bandera de victoria
		seg_write(seg); // actualiza display
	}

uint8_t actual4 = PINC & (1 << PC4); // guarda valor actual de boton
if (aj1 && !actual4)
{
	if (!run && vic == 0) // si el valor de victoria es diferente de 0 bloque el contador del jugador 1
	{
		if (jug1 == 0x00) //si se esta en 0 y se da un click se enciende la primera led
		jug1 = 0x01;
		else if (jug1 < 0x08)
		jug1 <<= 1; // corrimiento hacia la izquierda
		if (jug1 == 0x08) // revisa si se llego al 1000
		vic = 1; // enciende bandera de victoria jugador 1
	}
}
aj1 = actual4;
}
ISR (PCINT0_vect)
{
uint8_t actual5 = PINB &(1 << PB4);
	if(aj2 && !actual5)
	{
		if (!run && vic == 0)
		{
			if (jug2 == 0x00)
			jug2 = 0x01;      
			else if (jug2 < 0x08)
			jug2 <<= 1;
			if (jug2 == 0x08)
			vic = 2;
		}
	}
	aj2 = actual5;
}

