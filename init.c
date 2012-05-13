/*!
 * \file init.c
 * \brief Inicializáló függvények
 * \date Created on: 2012.05.13.
 * \author Author: kovacst
 */

#include "init.h"
#include "lcd.h"

/*!
 * \brief Fő inicializáló rutin
 *
 * Ezt hívjuk meg a main()-ból, ami elvégzi az inicializálás
 * folyamatát.
 *
 * \param void
 * \return none
 */
void init(void) {
	init_LCD();
}

/*!
 * \brief LCD inicializálás
 * \param void
 * \return none
 */
void init_LCD(void) {
	lcd_init(LCD_DISP_ON);		//LCD init
	lcd_clrscr();				//LCD clear and cursor home
}

