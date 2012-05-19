/*
 * \file remain.c
 * \brief Bekapcsolásig hátralévő idő függvényei.
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#include "remain.h"
#include "misc.h"
#include "setup.h"
#include "tempmeasure.h"
#include "trend.h"

static REMAIN remain;

/*!
 * \brief Remain init.
 * \param void
 * \return none
 */
void RemainInit(void) {
	remain.remain = REMAIN_OVERFLOW;
	remain.remain_unit = MIN;
}

/*!
 * \brief Bekapcsolásig hátralévő időt adja vissza.
 * \param void
 * \return remain.remain unsigned int
 */
unsigned int RemainGet(void) {
	signed char remain_temp;
	if(SetupGetMode() == MODE_ABS) {
		remain_temp = SetupGetOnTemp() - TempGet(NAPKOLLEKTOR_CH);
	} else {
		remain_temp = SetupGetOnTemp() -
					  (TempGet(NAPKOLLEKTOR_CH) - TempGet(MEDENCE_CH));
	}
	if(remain_temp >= 0) {
		remain.remain = TrendGet() * remain_temp;
		if(TrendGetUnit() == SEC) {
			if(remain.remain > 59) {
				remain.remain = remain.remain / 60;
				remain.remain_unit = MIN;
			} else {
				remain.remain_unit = SEC;
			}
		} else {
			remain.remain_unit = MIN;
		}
	} else {
		remain.remain = 0;
		remain.remain_unit = SEC;
	}
	return remain.remain;
}

/*!
 * \brief Remain idő mértékegysége.
 * \param void
 * \return remain.remain_unit unsigned char
 */
unsigned char RemainGetUnit(void) {
	return remain.remain_unit;
}

