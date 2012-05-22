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
	setup.valid_on_temp = EEPROMReadOnTemp();
	setup.valid_mode = EEPROMReadMode();
	setup.tmp_mode = setup.valid_mode;
	setup.tmp_on_temp = setup.valid_on_temp;
}

/*!
 * \brief Bekapcsolási tmp metódust adja vissza a button-nak.
 * \param void
 * \return setup.setup_tmp_mode unsigned char
 */
unsigned char SetupGetTmpMode(void) {
	return setup.tmp_mode;
}

/*!
 * \brief Bekapcsolási tmp hőmérsékletet adja vissza a button-nak.
 * \param void
 * \return setup.setup_on_temp unsigned char
 */
unsigned char SetupGetTmpOnTemp(void) {
	return setup.tmp_on_temp;
}

/*!
 * \brief Bekapcsolási metódust adja vissza.
 * \param void
 * \return setup.setup_mode unsigned char
 */
unsigned char SetupGetMode(void) {
	return setup.valid_mode;
}

/*!
 * \brief Bekapcsolási hőmérsékletet adja vissza.
 * \param void
 * \return setup.setup_on_temp unsigned char
 */
unsigned char SetupGetOnTemp(void) {
	return setup.valid_on_temp;
}

/*!
 * \brief Napkolletor szenzor korrekció értékét adja vissza.
 * \param void
 * \return setup.koll_diff signed char
 */
signed char SetupGetKollDiff(void) {
	return setup.koll_diff;
}

/*!
 * \brief Medence szenzor korrekció értékét adja vissza.
 * \param void
 * \return setup.med_diff signed char
 */
signed char SetupGetMedDiff(void) {
	return setup.med_diff;
}


/*!
 * \brief Bekapcsolási mód változtatása.
 * \param value unsigned char
 * \return none
 */
void SetupWriteTmpMode(unsigned char value) {
	setup.tmp_mode = value;
}

/*!
 * \brief Bekapcsolási hőmérséklet változtatása.
 * \param value unsigned char
 * \return none
 */
void SetupWriteTmpOnTemp(unsigned char value) {
	setup.tmp_on_temp = value;
}

/*!
 * \brief Bekapcsolási mód érvényesítése és kiírása az EEPROM-ba.
 * \param void
 * \return none
 */
void SetupWriteMode(void) {
	setup.valid_mode = setup.tmp_mode;
	EEPROMWriteMode(setup.valid_mode);
}

/*!
 * \brief Bekapcsolási hőmérséklet változtatása.
 * \param void
 * \return none
 */
void SetupWriteOnTemp(void) {
	setup.valid_on_temp = setup.tmp_on_temp;
	EEPROMWriteOnTemp(setup.valid_on_temp);
}

/*!
 * \brief Napkolletor szenzor korrekció beállítása.
 *
 * Maximum +-15 °C-fok eltérítés engedünk.
 *
 * \param value signed char
 * \return none
 */
void SetupWriteKollDiff(signed char value, unsigned char save) {
	if(value > 15) value = 15;
	if(value < -15) value = -15;
	setup.koll_diff = value;
	if(save == WRITE_TO_EEPROM) {
		EEPROMWriteKollDiff((unsigned char)setup.koll_diff);
	}
}

/*!
 * \brief Medence szenzor korrekció beállítása.
 *
 * Maximum +-15 °C-fok eltérítés engedünk.
 *
 * \param value signed char
 * \return none
 */
void SetupWriteMedDiff(signed char value, unsigned char save) {
	if(value > 15) value = 15;
	if(value < -15) value = -15;
	setup.med_diff = value;
	if(save == WRITE_TO_EEPROM) {
		EEPROMWriteMedDiff((unsigned char)setup.med_diff);
	}
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
	setup.tmp_mode = setup.valid_mode;
	setup.tmp_on_temp = setup.valid_on_temp;
	setup.koll_diff = (signed char)EEPROMReadKollDiff();
	setup.med_diff = (signed char)EEPROMReadMedDiff();
}
