/*
 * \file pump.h
 * \brief Szivattyú vezérlő függvények
 * \date Created on: 2012.05.19.
 * \author Author: Tamas Kovacs
 */

#ifndef PUMP_H_
#define PUMP_H_

#define PUMP_CHECK_TIME 5		//**< Ennyi időnként vizsgáljuk a szivattyút kikapcsolásra */

typedef struct PUMP {
	unsigned long int prev_time; //**< a kiértékeléshez szükséges menteni az adott időpontot */
	unsigned char status;		 //**< szivattyú állapota (ON/OFF) */
	unsigned char prev_temp;	 //**< kiértékeléshez mentett előző mért hőmérséklet */
}PUMP;

void PumpInit(void);
void PumpRefresh(void);
unsigned char PumpGetStatus(void);

#endif /* PUMP_H_ */
