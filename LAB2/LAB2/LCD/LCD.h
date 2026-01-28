/*
 * LCD.h
 *
 * Created: 1/27/2026 11:54:35 AM
 *  Author: diego
 */ 

#include <avr/io.h>
#include <stdint.h>
#ifndef LCD_H_
#define LCD_H_

void setup_LCD_8(void);
void command_LCD(uint8_t com);
void char_LCD(uint8_t car);
void string_LCD(char *cad);
void clear_LCD(void);
void cursor_LCD(uint8_t fil, uint8_t col);




#endif /* LCD_H_ */