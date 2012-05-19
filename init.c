/*!
 * \file init.c
 * \brief Init processz függvényei
 * \date Created on: 2012.05.17.
 * \author Author: Tamas Kovacs
 */

#include "adc.h"
#include "screen.h"
#include "misc.h"
#include "timer.h"
#include "trend.h"
#include "setup.h"
#include "remain.h"
#include "eeprom.h"
#include "pump.h"
#include "lastfiveheating.h"
/*!
 * \brief Fő inicializáló függvény
 * \param void
 * \return none
 */
void Init(void) {
	EEPROMInit();
	TimerInit();
	ADCInit();
	SetupInit();
	PumpInit();
	RemainInit();
	TrendInit();
	LastHeatingInit();
	ScreenInit();
}
