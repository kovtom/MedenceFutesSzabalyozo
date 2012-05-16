/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "lcd.h"
#include "adc.h"
#include "tempmeasure.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

int main(void) {

	char buffer[5];

	ADCInit();

	lcd_init(LCD_DISP_ON);		//LCD init
	lcd_clrscr();				//LCD clear and cursor home
	lcd_puts("Ezt irjuk ki");	//LCD-re string kiirasa

	for (;;) {
		//unsigned int temp;
		//temp = ADCGet(MEDENCE_CH);

		unsigned char temp;
		temp = GetTemp(MEDENCE_CH);
		lcd_gotoxy(0,1);
		itoa(temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc(0xDF); lcd_putc('C');
		//_delay_ms(100);
	}
	return 0;
}
