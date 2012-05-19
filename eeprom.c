/*!
 * \file eeprom.c
 * \brief EEPROM kezelő függvények
 * \date Created on: 2012.05.19.
 * \author Author: Tamas Kovacs
 */

#include "eeprom.h"
#include "misc.h"
#include <avr/eeprom.h>

static EEPROM_S EEMEM eeprom;

/*!
 * \brief EEPROM Inicializálás
 *
 * EEPROM alap adatokkal való feltöltése. Csak a fejlesztés során használjuk
 * majd.
 *
 * \param void
 * \return none
 */
void EEPROMInit(void) {
	unsigned char tmp[] = { 10, 20, 30, 34, 67 };
	EEPROMWriteMode(MODE_KUL);
	EEPROMWriteOnTemp(20);
	EEPROMWriteLastFive(tmp);
	EEPROMWriteTotalPumpTime(5420);
}

/*!
 * \brief EEPROM-ba bekapcsolási metódus
 * \param value unsigned char
 * \return none
 */
void EEPROMWriteMode(unsigned char value) {
	eeprom_update_byte(&eeprom.mode, value);
}

/*!
 * \brief EEPROM-ba bekapcsolási hőmérséklet
 * \param value unsigned char
 * \return none
 */
void EEPROMWriteOnTemp(unsigned char value) {
	eeprom_update_byte(&eeprom.on_temp, value);
}

/*!
 * \brief EEPROM-ba utólsó öt bekapcsolás
 * \param *value unsigned char pointer
 * \return none
 */
void EEPROMWriteLastFive(unsigned char * value) {
	eeprom_write_block(value, eeprom.last_five, 5);
}

/*!
 * \brief EEPROM-ba Összes szivattyú üzemidő
 * \param value unsigned long int
 * \return none
 */
void EEPROMWriteTotalPumpTime(unsigned long int value) {
	eeprom_update_dword(&eeprom.total_pump_time, value);
}

/*!
 * \brief EEPROM-ból bekapcsolási metódus
 * \param void
 * \return eeprom.mode unsigned char
 */
unsigned char EEPROMReadMode(void) {
	return eeprom_read_byte(&eeprom.mode);
}

/*!
 * \brief EEPROM-ból bekapcsolási hőmérséklet
 * \param void
 * \return eeprom.on_temp unsigned char
 */
unsigned char EEPROMReadOnTemp(void) {
	return eeprom_read_byte(&eeprom.on_temp);
}

/*!
 * \brief EEPROM-ból utolsó öt felfűtési időtartam tömbbe
 * \param *value unsigned char pointer
 * \return void
 */
void EEPROMReadLastFive(unsigned char * value) {
	eeprom_read_block(value, eeprom.last_five, 5 );
}

/*!
 * \brief EEPROM-ból összes szivattyú üzemidő
 * \param void
 * \return eeprom.total_pump_time unsigned long int
 */
unsigned long int EEPROMReadTotalPumpTime(void) {
	return eeprom_read_dword(&eeprom.total_pump_time);
}


















