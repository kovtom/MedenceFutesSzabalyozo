/*!
 * \file screen.c
 * \brief Screen kezelő függvények
 * \date Created on: 2012.05.16.
 * \author Author: Tamas Kovacs
 */

#include "misc.h"
#include "screen.h"
#include "lcd.h"
#include <avr/pgmspace.h>
#include <stdlib.h>

static const char string0[] PROGMEM = "Medence:";
static const char string1[] PROGMEM = "Napkoll:";
static const char string2[] PROGMEM = "Utolso 5 felfutesi ido:";
static const char string3[] PROGMEM = "perc";
static const char string4[] PROGMEM = "Beallitasok";
static const char string5[] PROGMEM = "Bekapcs. mod:";
static const char string6[] PROGMEM = "<abszolut>";
static const char string7[] PROGMEM = "<kulonbseg>";
static const char string8[] PROGMEM = "Bekapcs. hofok:";
static const char string9[] PROGMEM = "(1):";
static const char string10[] PROGMEM = "(2):";

/*!
 * \brief Stringek tárolása program memóriában
 */
PGM_P string_table[] PROGMEM =
{
		string0,
		string1,
		string2,
		string3,
		string4,
		string5,
		string6,
		string7,
		string8,
		string9,
		string10,
};

volatile SCREEN screen;

/*!
 * \brief Screen inicializálás.
 * \param void
 * \return none
 */
void ScreenInit(void){
	screen.selector = 0;
}

/*!
 * \brief Screen kiválasztása.
 * \param selector_p (SCREEN_MAIN|SCREEN_LASTFIVE|SCREEN_SET_MODE|SCREEN_SET_TEMP)
 * \return none
 */
void ScreenSelector(unsigned char selector_p) {
	screen.selector = selector_p;
}

/*!
 * \brief Screen kiirasa LCD-re
 * \param void
 * \return none
 */
void ScreenRefresh(void) {
	char buffer[3];							//itoa eredményét tároljuk itt
	if(screen.selector == 0) {
		lcd_clrscr();						//lcd clear

		lcd_puts_p(string_table[MEDENCE]);	//Medence:20°C
		itoa(screen.med_temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc('C');
		lcd_putc(' ');

		lcd_putc('A');						//^12min/°C
		itoa(screen.trend, buffer, 10);
		lcd_puts(buffer);
		if(screen.trend_unit) {				//mértékegység választása
			lcd_putc('m'); lcd_putc('n');
		} else {
			lcd_putc('s'); lcd_putc('c');
		}
		lcd_putc('/');
		lcd_putc('C');
		lcd_putc(' ');

		lcd_puts("S:");						//S:ON
		if(screen.pump_state) {
			lcd_puts("BE\n");
		} else {
			lcd_puts("KI\n");
		}

		lcd_puts_p(string_table[NAPKOLL]);	//Napkoll:20°C
		itoa(screen.koll_temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc('C');
		lcd_putc(' ');

		lcd_puts("R:");						//R:20min
		itoa(screen.remain, buffer, 10);
		lcd_puts(buffer);
		if(screen.remain_unit) {
			lcd_putc('m'); lcd_putc('n');
		} else {
			lcd_putc('s'); lcd_putc('c');
		}
		lcd_putc(' ');

		lcd_puts("T:");						//T:20°C
		itoa(screen.on_temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc('c');
		//*****>> innen folytatni

	}
}




void ScreenSet_med_temp(unsigned char);
void ScreenSet_koll_temp(unsigned char);
void ScreenSet_trend(unsigned char);
void ScreenSet_trend_unit(unsigned char);
void ScreenSet_pump_state(unsigned char);
void ScreenSet_remain(unsigned char);
void ScreenSet_remain_unit(unsigned char);
void ScreenSet_on_temp(unsigned char);
void ScreenSet_last_heat(unsigned char);
void ScreenSet_mode(unsigned char);
