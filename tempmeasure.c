/*
 * \file tempmeasure.c
 * \brief Napkollektorral kapcsolatos függvények
 *
 * \date Created on: 2012.05.16.
 * \author Author: Tamas Kovacs
 */

#include "tempmeasure.h"
#include "misc.h"
#include "adc.h"
#include <avr/io.h>

#ifdef DEBUG_TEMPMEASURE
	#include "timer.h"
	#include "pump.h"
	static unsigned long int prev_med_time;
	static unsigned long int prev_koll_time;
	static unsigned char koll_temp = 21;
	static unsigned char med_temp = 21;
#endif

/*!
 * \brief Hőmérséklet mérés
 *
 * Az eredményt Celsius fokban kapjuk vissza
 *
 * \param channel unsigned char channel
 * \return celsius unsigned int celsius fokra kerekítve
 */
unsigned char TempGet(unsigned char channel) {
#ifndef DEBUG_TEMPMEASURE
	uint32_t measured = 0;
	uint16_t celsius;
	unsigned char tmp;
	for(unsigned char i = 0; i < AVERAGE_COUNT; i++) {
		measured += (uint32_t)(ADCGet(channel));
	}
	measured = measured / AVERAGE_COUNT;
	celsius = ((measured * 50000) / 1024) - 27315; //50000->5V; 27315->0°C
	tmp = celsius % 100;						   //tmp = törtrész
	tmp = tmp / 50;								   //ha tmp >= 50 akkor felfelé kerekítünk
	celsius = (celsius / 100) + tmp;			   //kerekítést hozzáadjuk
	if(channel == MEDENCE_CH) {
		return 21;
	} else {
		return (unsigned char)celsius;
	}
#else
	if(channel == NAPKOLLEKTOR_CH) {
		if((TimeGetNow() - prev_koll_time)/50 > 1) {
			prev_koll_time = TimeGetNow();
			if(PumpGetStatus() == PUMP_OFF ||
					PumpGetStatus() == PUMP_ERROR) {
				koll_temp++;
			} else {
				if(koll_temp != TempGet(MEDENCE_CH)) {
					koll_temp--;
				}
			}
		}
		return koll_temp;
	} else {
		if((TimeGetNow() - prev_med_time)/50 > 120) {
			med_temp++;
			prev_med_time = TimeGetNow();
		}
		return med_temp;
	}
#endif
}
