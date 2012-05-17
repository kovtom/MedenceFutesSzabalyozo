/*!
 * \file init.c
 * \brief Init processz függvényei
 * \date Created on: 2012.05.17.
 * \author Author: Tamas Kovacs
 */

#include "adc.h"
#include "screen.h"
#include "misc.h"

/*!
 * \brief Fő inicializáló függvény
 * \param void
 * \return none
 */
void Init(void) {
	ADCInit();
	ScreenInit();
}
