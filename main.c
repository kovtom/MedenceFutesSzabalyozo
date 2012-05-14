/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "init.h"
#include "lcd.h"
#include "strings.h"
#include <avr/io.h>

#include <util/delay.h>

//extern const char * StringPointers[];

int main(void) {

	init();						//init RESET után

	lcd_clrscr();
	lcd_puts_p(StringPointers[s_Medence]);
	lcd_puts("21");
	lcd_put_CELSIUS;
	lcd_putc('\n');
	lcd_puts_p(StringPointers[s_Napkoll]);
	lcd_puts("18");
	lcd_put_min;
	_delay_ms(5000);

    lcd_clrscr();   /* clear display home cursor */

    lcd_puts("Copyright: ");


    lcd_gotoxy(0,1);
    for(uint8_t i = 0; i < DEFINED_CHAR; i++) {
    	lcd_putc(i);
    }
    //lcd_putc(' ');
    //lcd_puts("21"); lcd_putc(4);

	for (;;);					//Loop...
	return 0;
}
