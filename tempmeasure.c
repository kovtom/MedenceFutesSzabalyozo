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
#include "timer.h"
#include <avr/io.h>

#ifdef DEBUG_TEMPMEASURE
	#include "timer.h"
	#include "pump.h"
	static unsigned long int prev_med_time;
	static unsigned long int prev_koll_time;
	static unsigned char koll_temp = 21;
	static unsigned char med_temp = 21;
#endif

static TEMPMEASURE tempmeasure;

/*!
 * \brief Privát függvény, mely visszaadja az aktuális hőmérsékletet
 * \param channel unsigned char
 * \return value unsigned char
 */
static unsigned char Tempmeasure(unsigned char channel) {
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
		if((TimeGetNow() - prev_koll_time)/50 > 6) {
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
		if((TimeGetNow() - prev_med_time)/50 > 3600) {
			med_temp++;
			prev_med_time = TimeGetNow();
		}
		return med_temp;
	}
#endif
}

/*!
 * \brief Kezdeti hőmérsékletek beállítása
 * \param void
 * \return none
 */
void TempmeasureInit(void) {
	tempmeasure.med_temp = Tempmeasure(MEDENCE_CH);
	tempmeasure.koll_temp = Tempmeasure(NAPKOLLEKTOR_CH);
	tempmeasure.prev_time = TimeGetNow();
}
/*!
 * \brief Hőmérséklet mérés
 *
 * Az eredményt Celsius fokban kapjuk vissza.
 * Ha nem telt még el a DELAY_MEASURE akkor nem mérünk újra,
 * csak visszaadjuk a tárolt értéket.
 *
 * \param channel unsigned char channel
 * \return celsius unsigned int celsius fokra kerekítve
 */
unsigned char TempGet(unsigned char channel) {
	if(TimeGetNow() - tempmeasure.prev_time > DELAY_MEASURE) {  //Eltelt már a késleltetés ideje?
		tempmeasure.med_temp = Tempmeasure(MEDENCE_CH);			//ha igen akkor mérünk is és tárolunk
		tempmeasure.koll_temp = Tempmeasure(NAPKOLLEKTOR_CH);
		tempmeasure.prev_time = TimeGetNow();
	}
	if(channel == MEDENCE_CH) {							//Visszaadjuk a tárolt értéket
		return tempmeasure.med_temp;
	} else {
		return tempmeasure.koll_temp;
	}
}
