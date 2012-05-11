/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "lcd.h"
#include <avr/io.h>

int main(void) {

	lcd_init(LCD_DISP_ON);		//LCD init
	lcd_clrscr();				//LCD clear and cursor home
	lcd_puts("Ezt irjuk ki");	//LCD-re string kiirasa

	for (;;);					//Loop...
	return 0;
}
