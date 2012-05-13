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

#define s_Medence 0
#define s_Napkoll 1

const char String1[] PROGMEM = "Medence:";
const char String2[] PROGMEM = "Napkoll:";

const char * StringPointers[] = {
								String1,
								String2 };

int main(void) {

	init();						//init RESET után

	lcd_puts_p(StringPointers[s_Medence]);
	lcd_puts_p(StringPointers[s_Napkoll]);

	for (;;);					//Loop...
	return 0;
}
