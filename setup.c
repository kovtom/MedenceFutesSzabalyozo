/*!
 * \file setup.c
 * \brief Setup adatokat visszaadó függvények
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#include "setup.h"
#include "misc.h"

static SETUP setup;

/*!
 * \brief Beolvassa az elmentett setup adatokat.
 * \param void
 * \return none
 */
void SetupInit(void) {
	setup.steup_on_temp = 30;
	setup.setup_mode = MODE_KUL;
}

/*!
 * \brief Bekapcsolási metódust adja vissza.
 * \param void
 * \return setup.setup_mode unsigned char
 */
unsigned char SetupGetMode(void) {
	return setup.setup_mode;
}

/*!
 * \brief Bekapcsolási hőmérsékletet adja vissza.
 * \param void
 * \return setup.setup_on_temp unsigned char
 */
unsigned char SetupGetOnTemp(void) {
	return setup.steup_on_temp;
}


