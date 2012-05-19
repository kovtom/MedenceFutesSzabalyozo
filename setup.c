/*!
 * \file setup.c
 * \brief Setup adatokat visszaadó függvények
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#include "setup.h"
#include "misc.h"
#include "eeprom.h"

static SETUP setup;

/*!
 * \brief Beolvassa az elmentett setup adatokat.
 * \param void
 * \return none
 */
void SetupInit(void) {
	setup.setup_on_temp = EEPROMReadOnTemp();
	setup.setup_mode = EEPROMReadMode();
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
	return setup.setup_on_temp;
}

/*!
 * \brief Bekapcsolási hőmérséklet változtatása.
 * \param value unsigned char
 * \return none
 */
void SetupWriteOnTemp(unsigned char value) {
	setup.setup_on_temp = value;
}

/*!
 * \brief Bekapcsolási mód változtatása.
 * \param value unsigned char
 * \return none
 */
void SetupWriteMode(unsigned char value) {
	setup.setup_mode = value;
}
