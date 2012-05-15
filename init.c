/*!
 * \file init.c
 * \brief Inicializáló függvények
 * \date Created on: 2012.05.13.
 * \author Author: kovacst
 */

#include "init.h"
#include "lcd.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

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
	defineChars();
	init_Timer();
}

/*!
 * \brief LCD inicializálás
 * \param void
 * \return none
 */
void init_LCD(void) {
	lcd_init(LCD_DISP_ON);		//LCD init
}

/*!
 * \brief Saját karakterek definíciója
 * \param void
 * \return none
 */
void defineChars(void) {
	lcd_command(_BV(LCD_CGRAM));  /* set CG RAM start address 0 */
    for(uint8_t i = 0; i < (DEFINED_CHAR * 8); i++) {
        lcd_data(pgm_read_byte_near(&defChar[i]));
    }
}

/*!
 * \Timer inicializálás
 *
 * Timer beállítása, melynek számlálójából, majd az időadatokat
 * nyerjük
 *
 * \param void
 * \return none
 */
void init_Timer(void) {
	TCNT0 = 0;				//reset TCNT
	TIMSK |= _BV(TOIE0);	//overflow interrupt enable
	TCCR0 |= _BV(CS02);		//prescaler 256 ez 3.2768MHz-n 20msec overflow
	sei();					//interrupt enable
}

