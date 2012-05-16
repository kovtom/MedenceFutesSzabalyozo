/*
 * \file tempmeasure.c
 * \brief Napkollektorral kapcsolatos függvények
 *
 * \date Created on: 2012.05.16.
 * \author Author: Tamas Kovacs
 */

#include "tempmeasure.h"
#include "adc.h"
#include <avr/io.h>

/*!
 * \brief Hőmérséklet mérés
 *
 * Az eredményt Celsius fokban kapjuk vissza
 *
 * \param channel unsigned char channel
 * \return celsius unsigned int celsius fokra kerekítve
 */
unsigned char GetTemp(unsigned char channel) {
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
	return (unsigned char)celsius;
}

