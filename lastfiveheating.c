/*
 * \file lastfiveheating.c
 * \brief Utolsó öt felfűtést kiértékelő függvények
 * \date Created on: 2012.05.19.
 * \author Author: Tamas Kovacs
 */

#include "lastfiveheating.h"
#include "misc.h"
#include "eeprom.h"
#include "timer.h"
#include "pump.h"

static LASTHEATING lastheating;

/*!
 * \brief LastHeating inicializálás.
 * \param void
 * \return none
 */
void LastHeatingInit(void) {
	lastheating.prev_pump_state = PUMP_ON;
	lastheating.measure_status = FALSE;
	unsigned int tmp[5];
	EEPROMReadLastFive(tmp);
	for(unsigned char i = 0; i < 5; i++) {
		lastheating.heating_time[i] = tmp[i];
	}
}

/*!
 * \brief LastHeating újraszámolása, frissítése.
 * \param void
 * \return none
 */
void LastHeatingRefresh(void) {
	if(PumpGetStatus() == PUMP_ERROR) {		//Ha pump error van nem mérünk
		return;
	}
	if(lastheating.prev_pump_state == PUMP_ON &&
			PumpGetStatus() == PUMP_OFF) {
		lastheating.prev_time = TimeGetNow();
		lastheating.measure_status = TRUE;
		lastheating.prev_pump_state = PUMP_OFF;
	} else {
		if(lastheating.measure_status) {
			if(lastheating.prev_pump_state == PUMP_OFF &&
					PumpGetStatus() == PUMP_ON) {
				unsigned long int tmp;
				tmp = ((TimeGetNow() - lastheating.prev_time) / TICK_SEC) / 60;
				for(unsigned char i = 4; i > 0; i--) {
					lastheating.heating_time[i] = lastheating.heating_time[i - 1];
				}
				if(tmp < LASTHEAT_MAX + 1) {
					lastheating.heating_time[0] = (unsigned int)tmp;
				} else {
					lastheating.heating_time[0] = LASTHEAT_MAX;
				}
				lastheating.measure_status = FALSE;
				lastheating.prev_pump_state = PUMP_ON;
			}
		}
	}
}

/*!
 * \brief LastHeating értékének visszaadása.
 * \param value unsigned char pointer
 * \return none
 */
void LastHeatingGet(unsigned int *value) {
	for(unsigned char i = 0; i < 5; i++) {
		value[i] = lastheating.heating_time[i];
	}
}















