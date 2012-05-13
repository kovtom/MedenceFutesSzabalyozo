/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "init.h"
#include "lcd.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define s_Medence 0
#define s_Napkoll 1

static const PROGMEM unsigned char copyRightChar[] = {
		0x07, 0x08, 0x13, 0x14, 0x14, 0x13, 0x08, 0x07,
		0x00, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00
};

const PROGMEM char String1[] = "Medence:";
const PROGMEM char String2[] = "Napkoll:";

const char * StringPointers[] = {
		String1,
		String2
};

int main(void) {

	init();						//init RESET után

	lcd_puts_p(StringPointers[s_Medence]);
	lcd_puts_p(StringPointers[s_Napkoll]);
	_delay_ms(2000);

    lcd_clrscr();   /* clear display home cursor */

    lcd_puts("Copyright: ");

    lcd_command(_BV(LCD_CGRAM));  /* set CG RAM start address 0 */
    for(uint8_t i=0; i<16; i++)
    {
        lcd_data(pgm_read_byte_near(&copyRightChar[i]));
    }
    lcd_gotoxy(0,1);
    lcd_putc(0);
    lcd_putc(1);

	for (;;);					//Loop...
	return 0;
}
