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
#include "lastfiveheating.h"
#include "pump.h"
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
static const char string19[] PROGMEM = "Szivattyu ossz. uzemido:\n";
static const char string20[] PROGMEM = "d  ";
static const char string21[] PROGMEM = "h  ";
static const char string22[] PROGMEM = "Mentett adatok torlese:\nOssz.uzem/Utolso f. <OK>";
static const char string23[] PROGMEM = "(3):";
static const char string24[] PROGMEM = "(4):";
static const char string25[] PROGMEM = "Napkoll. kalibr.:";
static const char string26[] PROGMEM = "Medence. kalibr.:";

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
		string18,
		string19,
		string20,
		string21,
		string22,
		string23,
		string24,
		string25,
		string26
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
	screen.prev_selector = 0xFF;  //érvénytelen selector, hogy elsőre legyen kiirás
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
 * \brief Következő képernyő beállítása.
 * \param void
 * \return none
 */
void ScreenNextSelector(void) {
	if(screen.selector == SCREEN_NUMBER) {
		screen.selector = 0;
	} else {
		screen.selector++;
	}
}

/*!
 * \brief Screen értékének visszaadása.
 * \param void
 * \return screen.selector unsigned char
 */
unsigned char ScreenGetSelector(void) {
	return screen.selector;
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
		lcd_puts_p(string_table[MEDENCE_S]);	//Medence:20°C
		itoa(TempGet(MEDENCE_CH), buffer, 10);
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');

		lcd_putc(FELNYIL);					//^12min/°C
		signed char trend = TrendGet();
		if(trend < 0 || trend > 99) trend = 99;
		itoa(trend, buffer, 10);
		if(trend < 10) lcd_putc(' '); //ha a számérték egy számjegyű elé
		lcd_puts(buffer);					 //teszünk egy space-t
		if(TrendGetUnit() == MIN) {				//mértékegység választása
			LCD_PUTS_MIN;
		} else {
			LCD_PUTS_SEC;
		}
		lcd_putc('/');
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');

		lcd_puts_p(string_table[PUPM_STATE_S]); //S:ON
		if(PumpGetStatus() == PUMP_ON) {
			lcd_puts_p(string_table[BE_S]);
		} else if(PumpGetStatus() == PUMP_OFF) {
			lcd_puts_p(string_table[KI_S]);
		} else {
			lcd_puts_p(string_table[PUMP_ERROR_S]);
		}

		lcd_puts_p(string_table[NAPKOLL_S]);	//Napkoll:20°C
		itoa(TempGet(NAPKOLLEKTOR_CH), buffer, 10);
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');

		lcd_puts_p(string_table[REMAIN_S]);						//R:20min
		signed char remain = RemainGet();
		if(remain < 0 || remain > 99) remain = 99;
		itoa(remain, buffer, 10);
		if(remain < 10) lcd_putc(' ');	//ha a számérték egy számjegyű
		lcd_puts(buffer);						//akkor elé teszünk egy space-t
		if(RemainGetUnit() == MIN) {
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
		itoa(SetupGetOnTemp(), buffer, 10);
		if(SetupGetOnTemp() < 10) lcd_putc(' ');
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
	}

	else if(screen.selector == SCREEN_LASTFIVE) {
		lcd_puts_p(string_table[UTOLSO_5_S]); lcd_putc('\n');	//Utolso 5 felfutesi ido:
		unsigned int * lastheat;
		lastheat = LastHeatingGet();
		for(unsigned char i = 0; i < 5; i++) {				//123,123,123,123,123 perc
			itoa(lastheat[i], buffer, 10);
			lcd_puts(buffer);
			if(i < 4) lcd_putc(',');
		}
		lcd_putc(' ');
		lcd_puts_p(string_table[PERC_S]);
	}

	else if(screen.selector == SCREEN_SET_MODE) {
		lcd_puts_p(string_table[BEALLITASOK_S]);			//Beallitasok(1):
		lcd_puts_p(string_table[B1_S]); lcd_putc('\n');	//Bekapcs. mod:<abszolut>
		lcd_puts_p(string_table[BEKAPCSMOD_S]);
		if(SetupGetTmpMode() == MODE_ABS) {
			lcd_puts_p(string_table[ABSZOLUT_S]);
			lcd_putc(' ');
		} else {
			lcd_puts_p(string_table[KULONBSEG_S]);
		}
	}

	else if(screen.selector == SCREEN_SET_TEMP) {
		lcd_puts_p(string_table[BEALLITASOK_S]);			//Beallitasok(2):
		lcd_puts_p(string_table[B2_S]); lcd_putc('\n');	//Bekapcs. hofok: ^20Cˇ
		lcd_puts_p(string_table[BEKAPCSHOF_S]);
		lcd_putc(' ');
		lcd_putc(FEL_C);
		lcd_putc(' ');
		itoa(SetupGetTmpOnTemp(), buffer, 10);
		lcd_puts(buffer);
		lcd_putc(CELSIUS_C);
		lcd_putc(' ');
		lcd_putc(LE_C);
	}

	else if(screen.selector == SCREEN_ALL_OP_TIME) {
		lcd_puts_p(string_table[ALL_TIME_S]);			//Szivattyu ossz. uzemido:

		itoa(PumpGetOpDay(), buffer, 10);
		lcd_puts(buffer);
		lcd_puts_p(string_table[DAY_S]);

		itoa(PumpGetOpHour(), buffer, 10);
		lcd_puts(buffer);
		lcd_puts_p(string_table[HOUR_S]);

		itoa(PumpGetOpMin(), buffer, 10);
		lcd_puts(buffer);
		lcd_putc(MIN_C1); lcd_putc(MIN_C2);
		lcd_puts("  ");

		itoa(PumpGetOpSec(), buffer, 10);
		lcd_puts(buffer);
		lcd_putc(SEC_C1); lcd_putc(SEC_C2);
	}

	else if(screen.selector == SCREEN_SET_SAVED_CLR) {
		lcd_puts_p(string_table[SETUP_SAVED_CLEAR_S]);
	}

	else if(screen.selector == SCREEN_SET_KOLL_KORR) {
		lcd_puts_p(string_table[BEALLITASOK_S]);
		lcd_puts_p(string_table[B3_S]);

		itoa(TempGet(NAPKOLLEKTOR_CH), buffer, 10);
		lcd_putc(' ');
		lcd_puts(buffer); lcd_putc(CELSIUS_C); lcd_putc('\n');
		lcd_puts_p(string_table[KOLL_KORR_S]); lcd_putc(' ');

		lcd_putc(FEL_C);
		itoa(SetupGetKollDiff(), buffer, 10); lcd_putc(' ');
		lcd_puts(buffer); lcd_putc(' ');
		lcd_putc(LE_C); lcd_putc(' ');
	}

	else if(screen.selector == SCREEN_SET_MED_KORR) {
		lcd_puts_p(string_table[BEALLITASOK_S]);
		lcd_puts_p(string_table[B4_S]);

		itoa(TempGet(MEDENCE_CH), buffer, 10);
		lcd_putc(' ');
		lcd_puts(buffer); lcd_putc(CELSIUS_C); lcd_putc('\n');
		lcd_puts_p(string_table[MED_KORR_S]); lcd_putc(' ');

		lcd_putc(FEL_C);
		itoa(SetupGetMedDiff(), buffer, 10); lcd_putc(' ');
		lcd_puts(buffer); lcd_putc(' ');
		lcd_putc(LE_C); lcd_putc(' ');
	}

	else {
		lcd_puts_p(string_table[ERROR_S]);
	}
}
