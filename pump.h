/*
 * \file pump.h
 * \brief Szivattyú vezérlő függvények
 * \date Created on: 2012.05.19.
 * \author Author: Tamas Kovacs
 */

#ifndef PUMP_H_
#define PUMP_H_

#define PUMP_CHECK_TIME 60		//**< Ennyi időnként vizsgáljuk a szivattyút kikapcsolásra */
#define PUMP_RELAY_DIR DDRD			//**< Szivattyú relé DIR reg. */
#define PUMP_RELAY_PORT PORTD			//**< Szivattyú relé PORT */
#define PUMP_RELAY PD3				//**< Szivattyú PIN */

typedef struct PUMP {
	unsigned long int prev_time; //**< a kiértékeléshez szükséges menteni az adott időpontot */
	unsigned char status;		 //**< szivattyú állapota (ON/OFF) */
	unsigned char prev_temp;	 //**< kiértékeléshez mentett előző mért hőmérséklet */
}PUMP;

typedef struct OPERATIONTIME {
	unsigned long int prev_time;	//**< a kiértékeléshez szükséges */
	unsigned char prev_pump_state;	//**< a kiértékeléshez szükséges */
	unsigned long int all_time;		//**< teljes üzemidő másodpercben */
	unsigned int day;				//**< teljes üzemidő nap összetevő */
	unsigned char hour;				//**< teljes üzemidő óra összetevő */
	unsigned char min;				//**< teljes üzemidő perc összetevő */
	unsigned char sec;				//**< teljes üzemidő másodperc összetevő */

}OPERATIONTIME;

void PumpInit(void);
void PumpRefresh(void);
unsigned char PumpGetStatus(void);
//static void PumpOpTimeRefresh(void);
unsigned int PumpGetOpDay(void);
unsigned char PumpGetOpHour(void);
unsigned char PumpGetOpMin(void);
unsigned char PumpGetOpSec(void);
//static void PumpOpCalc(void);

#endif /* PUMP_H_ */
