/*!
 * \file timer.c
 * \brief Timer tick kezelő függvények
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

/*!
 * \brief Aktuális időt adja vissza
 *
 * A bekapcsolás vagy RESET óta eltelt idő/20 msec számláló értékét adja vissza.
 *
 * \param void
 * \return uint32_t time
 */

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile static unsigned long int time;

void InitTimer(void) {
	TIMSK |= _BV(TOIE0);			//Timer overflow interrupt engedélyezés
	TCCR0 |= PRESCALER_256;			//256-os osztóval indítjuk a Timer0-t
	sei();							//Interrupt enable
}

unsigned long int TimeGetNow(void) {
	return time;
}

ISR(TIMER0_OVF_vect) {
	time++;
}


