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
#include "button.h"
#include <avr/io.h>

static PUMP pump;
static OPERATIONTIME optime;

/*!
 * \brief Szivattyú day,hour stb... kiszámolása.
 * \param void
 * \return none
 */
static void PumpOpCalc(void) {
	unsigned long int tmp = optime.all_time;
	optime.day = tmp / 86400;
	tmp = tmp % 86400;
	optime.hour = tmp / 3600;
	tmp = tmp % 3600;
	optime.min = tmp / 60;
	optime.sec = tmp % 60;
}

/*!
 * \brief Szivattyú összes üzemállapot frissítése
 * \param void
 * \return none
 */
static void PumpOpTimeRefresh(void) {
	if(optime.prev_pump_state == PUMP_OFF &&
			PumpGetStatus() == PUMP_ON) {
		optime.prev_time = TimeGetNow();
		optime.prev_pump_state = PUMP_ON;
	} else {
		if(optime.prev_pump_state == PUMP_ON &&
				PumpGetStatus() == PUMP_OFF) {
			optime.all_time = optime.all_time +
					(TimeGetNow() - optime.prev_time) / TICK_SEC;
			PumpOpCalc();
			optime.prev_pump_state = PUMP_OFF;
		}
	}
}

/*!
 * \brief Szivattyú all_time mentése.
 *
 * PUMP_SAVE_TIME időnként mentjük az EEPROM-ba a szivattyú összes
 * üzemidejét.
 *
 * \param void
 * \return none
 */
static void PumpSaveAllTime(void) {
	if((TimeGetNow() - optime.last_save_time) / TICK_SEC > PUMP_SAVE_TIME) {
		optime.last_save_time = TimeGetNow();
		EEPROMWriteTotalPumpTime(optime.all_time);
		ButtonBeep(20);
	}
}

/*!
 * \brief Szivattyú állapotot inicializáció.
 * \param void
 * \return none
 */
void PumpInit(void) {
	PUMP_RELAY_DIR |= _BV(PUMP_RELAY);
	pump.status = PUMP_OFF;
	optime.prev_pump_state = PUMP_OFF;
	optime.all_time = EEPROMReadTotalPumpTime();
	PumpOpCalc();
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
				PUMP_RELAY_PORT &= ~_BV(PUMP_RELAY);
				ButtonBeep(3);
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
			PUMP_RELAY_PORT |= _BV(PUMP_RELAY);
			ButtonBeep(3);
			pump.status = PUMP_ON;

		}
	}
	PumpOpTimeRefresh();
	PumpSaveAllTime();
}

/*!
 * \brief Szivattyú összes üzem nap összetevő
 * \param void
 * \return optime.day unsigned int
 */
unsigned int PumpGetOpDay(void) {
	return optime.day;
}

/*!
 * \brief Szivattyú összes üzem óra összetevő
 * \param void
 * \return optime.hour unsigned char
 */
unsigned char PumpGetOpHour(void) {
	return optime.hour;
}

/*!
 * \brief Szivattyú összes üzem perc összetevő
 * \param void
 * \return optime.min unsigned char
 */
unsigned char PumpGetOpMin(void) {
	return optime.min;
}

/*!
 * \brief Szivattyú összes üzem másodperc összetevő
 * \param void
 * \return optime.sec unsigned char
 */
unsigned char PumpGetOpSec(void) {
	return optime.sec;
}

/*!
 * \brief Szivattyú összes üzemidő törlése.
 * \param void
 * \return none
 */
void PumpAllTimeClear(void) {
	optime.all_time = 0;
	PumpOpCalc();
	EEPROMWriteTotalPumpTime(optime.all_time);
}










