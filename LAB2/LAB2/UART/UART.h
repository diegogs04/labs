/*
 * UART.h
 *
 * Created: 2/2/2026 11:49:21 AM
 *  Author: diego
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

void UART_init(uint16_t ubrr);
void UART_TX_char(char dato_s);
void UART_TX_string(const char *str);
char UART_RX_char(void);
uint8_t RX_dispo(void);





#endif /* UART_H_ */