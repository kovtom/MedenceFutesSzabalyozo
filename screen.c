/*!
 * \file screen.c
 * \brief Screen kezelő függvények
 * \date Created on: 2012.05.16.
 * \author Author: Tamas Kovacs
 */

#include "misc.h"
#include "screen.h"
#include "lcd.h"
#include "trend.h"
#include "remain.h"
#include "tempmeasure.h"
#include "eeprom.h"
#include "setup.h"
#include <avr/pgmspace.h>
#include <stdlib.h>

/*!
 * \brief Saját karakterek.
 *
 * min, sec, °C, fel háromszög, le háromszög
 */
static const PROGMEM unsigned char defChar[] = {
		0x00, 0x00, 0x1a, 0x15, 0x15, 0x15, 0x15, 0x00,		//min
		0x00, 0x00, 0x16, 0x05, 0x15, 0x15, 0x15, 0x00,
		0x00, 0x00, 0x03, 0x04, 0x02, 0x01, 0x06, 0x00,		//sec
		0x00, 0x00, 0x19, 0x12, 0x1a, 0x12, 0x19, 0x00,
		0x18, 0x1b, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00,		//°C
		0x00, 0x04, 0x04, 0x0e, 0x0e, 0x1f, 0x1f, 0x00,		//fel
		0x00, 0x1f, 0x1f, 0x0e, 0x0e, 0x04, 0x04, 0x00,		//le
		0x04, 0x0e, 0x15, 0x04, 0x04, 0x04, 0x04, 0x00		//felnyíl
};

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
static const char string11[] PROGMEM = "Error";
static const char string12[] PROGMEM = "BE\n";
static const char string13[] PROGMEM = "KI\n";
static const char string14[] PROGMEM = "S:";
static const char string15[] PROGMEM = "R:";
static const char string16[] PROGMEM = "T=";
static const char string17[] PROGMEM = "**\n";
static const char string18[] PROGMEM = "T>";


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
		string11,
		string12,
		string13,
		string14,
		string15,
		string16,
		string17,
		string18
};

volatile SCREEN screen;

/*!
 * \brief Screen inicializálás.
 *
 * LCD inicializálás.
 * Saját karakterek feltöltése.
 * Main screen beállítása.
 *
 * \param void
 * \return none
 */
void ScreenInit(void){
	lcd_init(LCD_DISP_ON);									//init LCD
	lcd_command(_BV(LCD_CGRAM));  							//saját karakterek betöltése
	for(unsigned char i = 0; i < DEFINED_CHAR * 8; i++) {
		lcd_data(pgm_read_byte_near(&defChar[i]));
	}
	lcd_clrscr();											//clear LCD
	ScreenSelector(SCREEN_MAIN);   //kezdeti screen adatok beállítása
	ScreenSet_med_temp(TempGet(MEDENCE_CH));
	ScreenSet_trend(TrendGet());
	ScreenSet_trend_unit(TrendGetUnit());
	ScreenSet_pump_state(PUMP_OFF);
	ScreenSet_koll_temp(TempGet(NAPKOLLEKTOR_CH));
	ScreenSet_remain(REMAIN_MAX);
	ScreenSet_remain_unit(MIN);
	ScreenSet_on_temp(SetupGetOnTemp());
	screen.prev_selector = 0xFF;  //érvénytelen selector, hogy elsőre legyen kiirás
	unsigned char tmp[5];
	EEPROMReadLastFive(tmp);
	ScreenSet_last_heat(tmp);
	ScreenSet_mode(SetupGetMode());
}

/*!
 * \brief Screen kiválasztása.
 * \param value (SCREEN_MAIN|SCREEN_LASTFIVE|SCREEN_SET_MODE|SCREEN_SET_TEMP)
 * \return none
 */
void ScreenSelector(unsigned char value) {
	screen.selector = value;
}

/*!
 * \brief Screen kiirasa LCD-re
 * \param void
 * \return none
 */
void ScreenRefresh(void) {
	char buffer[3];							//itoa eredményét tároljuk itt
	if(screen.selector != screen.prev_selector) {	//ha az előző selector ua. volt akkor
		lcd_clrscr();								//nem törlünk, hogy ne villogjon az LCD
	} else {										//csak a kurzort mozgatjuk home-ba
		lcd_home();
	}
	screen.prev_selector = screen.selector;			//tároljuk az előző selectort

	if(screen.selector == SCREEN_MAIN) {
		lcd_puts_p(string_table[MEDENCE]);	//Medence:20°C
		itoa(screen.med_temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');

		lcd_putc(FELNYIL);					//^12min/°C
		itoa(screen.trend, buffer, 10);
		if(screen.trend < 10) lcd_putc(' '); //ha a számérték egy számjegyű elé
		lcd_puts(buffer);					 //teszünk egy space-t
		if(screen.trend_unit) {				//mértékegység választása
			LCD_PUTS_MIN;
		} else {
			LCD_PUTS_SEC;
		}
		lcd_putc('/');
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');

		lcd_puts_p(string_table[PUPM_STATE_S]); //S:ON
		if(screen.pump_state == PUMP_ON) {
			lcd_puts_p(string_table[BE_S]);
		} else if(screen.pump_state == PUMP_OFF) {
			lcd_puts_p(string_table[KI_S]);
		} else {
			lcd_puts_p(string_table[PUMP_ERROR_S]);
		}

		lcd_puts_p(string_table[NAPKOLL]);	//Napkoll:20°C
		itoa(screen.koll_temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');

		lcd_puts_p(string_table[REMAIN_S]);						//R:20min
		itoa(screen.remain, buffer, 10);
		if(screen.remain < 10) lcd_putc(' ');	//ha a számérték egy számjegyű
		lcd_puts(buffer);						//akkor elé teszünk egy space-t
		if(screen.remain_unit) {
			LCD_PUTS_MIN;
		} else {
			LCD_PUTS_SEC;
		}
		lcd_putc(' ');

		if(SetupGetMode() == MODE_ABS) {				//T:20°C
			lcd_puts_p(string_table[ON_TEMP_ABS_S]);
		} else {
			lcd_puts_p(string_table[ON_TEMP_KUL_S]);
		}
		itoa(screen.on_temp, buffer, 10);
		if(screen.on_temp < 10) lcd_putc(' ');
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
	}

	else if(screen.selector == SCREEN_LASTFIVE) {
		lcd_puts_p(string_table[UTOLSO_5]); lcd_putc('\n');	//Utolso 5 felfutesi ido:
		for(unsigned char i = 0; i < 5; i++) {				//123,123,123,123,123 perc
			itoa(screen.last_heat[i], buffer, 10);
			lcd_puts(buffer);
			if(i < 4) lcd_putc(',');
		}
		lcd_putc(' ');
		lcd_puts_p(string_table[PERC]);
	}

	else if(screen.selector == SCREEN_SET_MODE) {
		lcd_puts_p(string_table[BEALLITASOK]);			//Beallitasok(1):
		lcd_puts_p(string_table[B1]); lcd_putc('\n');	//Bekapcs. mod:<abszolut>
		lcd_puts_p(string_table[BEKAPCSMOD]);
		if(screen.mode) {
			lcd_puts_p(string_table[ABSZOLUT]);
		} else {
			lcd_puts_p(string_table[KULONBSEG]);
		}
	}

	else if(screen.selector == SCREEN_SET_TEMP) {
		lcd_puts_p(string_table[BEALLITASOK]);			//Beallitasok(2):
		lcd_puts_p(string_table[B2]); lcd_putc('\n');	//Bekapcs. hofok: ^20Cˇ
		lcd_puts_p(string_table[BEKAPCSHOF]);
		lcd_putc(' ');
		lcd_putc(FEL_C);
		lcd_putc(' ');
		itoa(screen.on_temp, buffer, 10);
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');
		lcd_putc(LE_C);
	}
	else {
		lcd_puts_p(string_table[ERROR_S]);
	}
}

/*!
 * \brief Medence hőmérséklet screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_med_temp(unsigned char value) {
	if(value > MED_TEMP_MAX) {
		screen.med_temp = MED_TEMP_MAX;
	} else {
		screen.med_temp = value;
	}
}

/*!
 * \brief Napkollektor hőmérséklet screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_koll_temp(unsigned char value) {
	if(value > NAPKOLL_TEMP_MAX) {
		screen.koll_temp = NAPKOLL_TEMP_MAX;
	} else {
		screen.koll_temp = value;
	}
}

/*!
 * \brief Hőmérséklet emelkedési trend screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_trend(unsigned int value) {
	if(value > TREND_MAX) {
		screen.trend = TREND_MAX;
	} else {
		screen.trend = value;
	}
}

/*!
 * \brief Hőmérséklet emelkedési trend mértékegysége screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_trend_unit(unsigned char value) {
	screen.trend_unit = value;
}

/*!
 * \brief Szivattyú státus screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_pump_state(unsigned char value) {
	screen.pump_state = value;
}

/*!
 * \brief Várható bekapcsolás ideje screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_remain(unsigned int value) {
	if(value > REMAIN_MAX) {
		screen.remain = REMAIN_MAX;
	} else {
		screen.remain = value;
	}
}

/*!
 * \brief Várható bekapcsolás ideje mértékegysége screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_remain_unit(unsigned char value) {
	screen.remain_unit = value;
}

/*!
 * \brief Bekapcsolási hőmérséklet screen-be.
 * \param value unsigned char
 * \return none
 */
void ScreenSet_on_temp(unsigned char value) {
	if(value > ONTEMP_MAX) {
		value = ONTEMP_MAX;
	} else {
		screen.on_temp = value;
	}
}

/*!
 * \brief Utlosó 5 felfütési idő screen-be.
 * \param value unsigned char pointer
 * \return none
 */
void ScreenSet_last_heat(unsigned char *value) {
	for(unsigned char i = 0; i < 5; i++) {
		screen.last_heat[i] = value[i];
	}
}

/*!
 * \brief Bekapcsolási metódus (abszolut/kulonbség)
 * \param value unsigned char
 * \return none
 */
void ScreenSet_mode(unsigned char value) {
	screen.mode = value;
}
