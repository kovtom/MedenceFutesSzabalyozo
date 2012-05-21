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
	setup.setup_valid_on_temp = EEPROMReadOnTemp();
	setup.setup_valid_mode = EEPROMReadMode();
	setup.setup_tmp_mode = setup.setup_valid_mode;
	setup.setup_tmp_on_temp = setup.setup_valid_on_temp;
}

/*!
 * \brief Bekapcsolási tmp metódust adja vissza a button-nak.
 * \param void
 * \return setup.setup_tmp_mode unsigned char
 */
unsigned char SetupGetTmpMode(void) {
	return setup.setup_tmp_mode;
}

/*!
 * \brief Bekapcsolási tmp hőmérsékletet adja vissza a button-nak.
 * \param void
 * \return setup.setup_on_temp unsigned char
 */
unsigned char SetupGetTmpOnTemp(void) {
	return setup.setup_tmp_on_temp;
}

/*!
 * \brief Bekapcsolási metódust adja vissza.
 * \param void
 * \return setup.setup_mode unsigned char
 */
unsigned char SetupGetMode(void) {
	return setup.setup_valid_mode;
}

/*!
 * \brief Bekapcsolási hőmérsékletet adja vissza.
 * \param void
 * \return setup.setup_on_temp unsigned char
 */
unsigned char SetupGetOnTemp(void) {
	return setup.setup_valid_on_temp;
}

/*!
 * \brief Bekapcsolási mód változtatása.
 * \param value unsigned char
 * \return none
 */
void SetupWriteTmpMode(unsigned char value) {
	setup.setup_tmp_mode = value;
}

/*!
 * \brief Bekapcsolási hőmérséklet változtatása.
 * \param value unsigned char
 * \return none
 */
void SetupWriteTmpOnTemp(unsigned char value) {
	setup.setup_tmp_on_temp = value;
}

/*!
 * \brief Bekapcsolási mód érvényesítése és kiírása az EEPROM-ba.
 * \param void
 * \return none
 */
void SetupWriteMode(void) {
	setup.setup_valid_mode = setup.setup_tmp_mode;
	EEPROMWriteMode(setup.setup_valid_mode);
}

/*!
 * \brief Bekapcsolási hőmérséklet változtatása.
 * \param void
 * \return none
 */
void SetupWriteOnTemp(void) {
	setup.setup_valid_on_temp = setup.setup_tmp_on_temp;
	EEPROMWriteOnTemp(setup.setup_valid_on_temp);
}

/*!
 * \brief Setup tmp undo.
 *
 * A MENU timeout után, vagy menu esetén a tmp adatok érvénytelenek. Visszaírjuk
 * az értékeiket a valid adatokra.
 *
 * \param void
 * \return none
 */
void SetupUndo(void) {
	setup.setup_tmp_mode = setup.setup_valid_mode;
	setup.setup_tmp_on_temp = setup.setup_valid_on_temp;
}
