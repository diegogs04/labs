/*
 * LCD.h
 *
 * Created: 1/27/2026 11:54:35 AM
 *  Author: diego
 */ 

#include <avr/io.h>
#ifndef LCD_H_
#define LCD_H_

void setup_LCD_8(void);
void command_LCD(com);
void char_LCD(car);
void string_LCD(char *cad);
void clear(void);
void cursor_LCD(uint8_t fil, uint8_t col);
void read_LCD(void);




#endif /* LCD_H_ */