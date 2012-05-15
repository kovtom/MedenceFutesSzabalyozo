/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "lcd.h"
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#define SPACE_LINE "                        "
uint8_t EEMEM counter_ee;

int main(void) {
	char buffer[4];

	lcd_init(LCD_DISP_ON);		//LCD init
	lcd_clrscr();				//LCD clear and cursor home
	lcd_puts("Ezt irjuk ki");	//LCD-re string kiirasa

	_delay_ms(2000);

	uint8_t counter;
	counter = eeprom_read_byte(&counter_ee);

	for (;;) {
		if(!(counter % 10)) {
			lcd_puts("Oszthato tizzel...");
			_delay_ms(2000);
			lcd_gotoxy(0,1);
			lcd_puts(SPACE_LINE);
			eeprom_update_byte(&counter_ee, counter);
		}
		itoa(counter, buffer, 10);
		lcd_gotoxy(0,1);
		lcd_puts(buffer);
		_delay_ms(1000);
		++counter;



	}
	return 0;
}
