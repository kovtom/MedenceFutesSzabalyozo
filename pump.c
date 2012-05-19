/*!
 * \file pump.c
 * \brief Szivattyú állapot kiértékelés
 * \date Created on: 2012.05.19.
 * \author Author: Tamas Kovacs
 */

#include "pump.h"
#include "misc.h"
#include "setup.h"
#include "tempmeasure.h"
#include "timer.h"
#include "trend.h"
#include "remain.h"
#include "eeprom.h"

static PUMP pump;

/*!
 * \brief Szivattyú állapotot inicializáció.
 * \param void
 * \return none
 */
void PumpInit(void) {
	pump.status = PUMP_OFF;
}

/*!
 * \brief Szivattyú állapotot adja vissza.
 * \param void
 * \return pump.status unsigned char
 */
unsigned char PumpGetStatus(void) {
	return pump.status;
}

/*!
 * \brief Szivattyú állapot frissítése
 * \param void
 * \return none
 */
void PumpRefresh(void) {
	signed char delta_temp;
	//Ha az abs beállított kisebb mint a medence hőfok akkor emelünk egyet
	//a beállított hőfokon.
	if(TempGet(MEDENCE_CH) >= SetupGetOnTemp() &&
			SetupGetMode() == MODE_ABS) {
		//SZIVATTYÚ KI
		pump.status = PUMP_ERROR;
		unsigned char tmp;
		tmp = SetupGetOnTemp();
		if(tmp < 99) {
			tmp++;
		}
		SetupWriteOnTemp(tmp);
		return;
	}
	//Ha a kulomb. beállított + medence > 99 fok
	if(SetupGetMode() == MODE_KUL &&
			(SetupGetOnTemp() + TempGet(MEDENCE_CH)) > 99 ) {
		//SZIVATTYÚ KI
		pump.status = PUMP_ERROR;
		unsigned char tmp;
		tmp = SetupGetOnTemp();
		if(tmp > 0) {
			--tmp;
		}
		SetupWriteOnTemp(tmp);
		return;
	}


	if(SetupGetMode() == MODE_ABS) {
		delta_temp = (signed char)SetupGetOnTemp() -
					 (signed char)TempGet(NAPKOLLEKTOR_CH);
	} else {
		delta_temp = (signed char)SetupGetOnTemp() -
					 ((signed char)TempGet(NAPKOLLEKTOR_CH) -
					  (signed char)TempGet(MEDENCE_CH));
	}
	if(pump.status == PUMP_ON) {
		if((TimeGetNow() - pump.prev_time) / TICK_SEC > PUMP_CHECK_TIME) {
			if(TempGet(NAPKOLLEKTOR_CH) == pump.prev_temp ||
					TempGet(NAPKOLLEKTOR_CH) == (pump.prev_temp + 1) ||
					TempGet(NAPKOLLEKTOR_CH) == (pump.prev_temp - 1) ||
					TempGet(NAPKOLLEKTOR_CH) < TempGet(MEDENCE_CH)) {
				//SZIVATTYÚ KI
				pump.status = PUMP_OFF;
				TrendClear();
			} else {
				pump.prev_temp = TempGet(NAPKOLLEKTOR_CH);
				pump.prev_time = TimeGetNow();
			}
		}
	} else {
		if(delta_temp <= 0) {
			pump.prev_time = TimeGetNow();
			pump.prev_temp = TempGet(NAPKOLLEKTOR_CH);
			//SZIVATTYÚ BE
			pump.status = PUMP_ON;

		}
	}
}

