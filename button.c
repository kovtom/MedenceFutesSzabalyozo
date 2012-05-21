/*
 * \file button.c
 * \brief Nyomógombokat kezelő függvények
 * \date Created on: 2012.05.20.
 * \author Author: Tamas Kovacs
 */

#include "button.h"
#include "timer.h"
#include "screen.h"
#include "misc.h"
#include "setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile static BUTTON button;

/*!
 * \brief Nyomógombok inicializálása.
 * \param void
 * \return none
 */
void ButtonInit(void) {
	BUTTON_BEEP_DIR |= _BV(BUTTON_BEEP);	//Piezo output

	BUTTON_MENU_PORT |= _BV(BUTTON_MENU);  //Pull-up enable
	BUTTON_UP_PORT |= _BV(BUTTON_UP);
	BUTTON_DOWN_PORT |= _BV(BUTTON_DOWN);
	BUTTON_OK_PORT |= _BV(BUTTON_OK);

	INT0_PORT |= _BV(INT0_PIN);				//INT0 pull up enable
	GICR |= _BV(INT0);						//INT0 engedélyezése (PD2-es lab)
	MCUCR |= _BV(ISC01);					//a láb lefutó élre adjon megszakítást
	sei();
}

/*!
 * \brief Menü funkció
 *
 * Menükezelésért felelő függvény.
 *
 * \param void
 * \return none
 */

void ButtonMenu(void){
	if(button.button) {								//Volt nyomógomb?
		ButtonBeep(1);
		button.prev_menu_time = TimeGetNow();		//Akkor volt aktivitás, timeout reset
		unsigned char tmp = ButtonGet();
		if(tmp == B_MENU) {				//Ha MENU volt akkor leptejuk a screen-t
			ScreenNextSelector();
			SetupUndo();
		} else {
			if(tmp == B_OK && ScreenGetSelector() == SCREEN_SET_MODE) {  //Ha Setup_mode-ban vagyunk és OK
				SetupWriteMode();
				ButtonBeep(10);
			}
			else if(tmp == B_OK && ScreenGetSelector() == SCREEN_SET_TEMP) {  //Ha Setup_on_temp-ben vagyunk és OK
							SetupWriteOnTemp();
							ButtonBeep(10);
			}
			else if((tmp == B_UP || tmp == B_DOWN) &&	 //Mod setup
					ScreenGetSelector() == SCREEN_SET_MODE) {
				if(SetupGetTmpMode() == MODE_ABS) {
					SetupWriteTmpMode(MODE_KUL);
				} else {
					SetupWriteTmpMode(MODE_ABS);
				}
			}
			else if(tmp == B_UP &&								//On temp setup UP
					ScreenGetSelector() == SCREEN_SET_TEMP &&
					SetupGetTmpOnTemp() < ONTEMP_MAX) {
				unsigned char tmp = SetupGetTmpOnTemp();
				tmp++;
				SetupWriteTmpOnTemp(tmp);
			}
			else if(tmp == B_DOWN &&							//On temp setup DOWN
					ScreenGetSelector() == SCREEN_SET_TEMP &&
					SetupGetTmpOnTemp() > 1) {
				unsigned char tmp = SetupGetTmpOnTemp();
				tmp--;
				SetupWriteTmpOnTemp(tmp);
			}
		}
	} else {
		if(TimeGetNow() - button.prev_menu_time > MENU_TIMEOUT) {
			ScreenSelector(SCREEN_MAIN);
			SetupUndo();
		}
	}
}

/*!
 * \brief Visszaadja a nyomógombok állapotát.
 *
 * Amikor meghívják a függvényt akkor a nyomogómb állapot törlődik.
 *
 * \param void
 * \return button.button unsigned char
 */
unsigned char ButtonGet(void) {
	unsigned char tmp = button.button;
	button.button = 0;
	return tmp;
}

/*!
 * \brief Nyomógom lenyomását érzékelő megszakítás.
 *
 * Az lenyomott gombot a BUTTON structúrában tárolja.
 *
 * \param void
 * \return none
 */
ISR(INT0_vect) {
	if(TimeGetNow() - button.prev_prell_time > 15) {
		if(bit_is_clear(BUTTON_MENU_PIN, BUTTON_MENU)) button.button |= _BV(0);
		if(bit_is_clear(BUTTON_UP_PIN, BUTTON_UP)) button.button |= _BV(1);
		if(bit_is_clear(BUTTON_DOWN_PIN, BUTTON_DOWN)) button.button |= _BV(2);
		if(bit_is_clear(BUTTON_OK_PIN, BUTTON_OK)) button.button |= _BV(3);
		button.prev_prell_time = TimeGetNow();
	}
}

/*!
 * \brief Hang a nyomógombhoz.
 *
 * Bemenet, hogy hányszor játsszuk le a beep-et.
 *
 * \param value unsigned char
 * \return none
 */
void ButtonBeep(unsigned char value) {
	for(unsigned char j = 0; j < value; j++) {
		for(unsigned char i = 0; i < 25; i++) {
			BUTTON_BEEP_PORT |= _BV(BUTTON_BEEP);
			_delay_us(500);
			BUTTON_BEEP_PORT &= ~_BV(BUTTON_BEEP);
			_delay_us(500);
		}
	}
}





