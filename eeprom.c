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
void EEPROMWriteLastFive(unsigned int * value) {
	for(unsigned char i = 0; i < 5; i++) {
		eeprom_update_word(&eeprom.last_five[i], value[i]);
	}
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
void EEPROMReadLastFive(unsigned int * value) {
	for(unsigned char i = 0; i < 5; i++) {
		value[i] = eeprom_read_word(&eeprom.last_five[i]);
	}
}

/*!
 * \brief EEPROM-ból összes szivattyú üzemidő
 * \param void
 * \return eeprom.total_pump_time unsigned long int
 */
unsigned long int EEPROMReadTotalPumpTime(void) {
	return eeprom_read_dword(&eeprom.total_pump_time);
}

/*!
 * \brief EEPROM-ból Napkollektor szenzor korrekció.
 * \param void
 * \return eeprom.koll_diff unsigned char
 */
unsigned char EEPROMReadKollDiff(void) {
	return eeprom_read_byte(&eeprom.koll_diff);
}

/*!
 * \brief EEPROM-ból Medence szenzor korrekció.
 * \param void
 * \return eeprom.med_diff unsigned char
 */
unsigned char EEPROMReadMedDiff(void) {
	return eeprom_read_byte(&eeprom.med_diff);
}

/*!
 * \brief EEPROM-ba Napkollektor szenzor korrekció.
 * \param value unsigned char
 * \return none
 */
void EEPROMWriteKollDiff(unsigned char value) {
	eeprom_update_byte(&eeprom.koll_diff, value);
}

/*!
 * \brief EEPROM-ba Medence szenzor korrekció.
 * \param value unsigned char
 * \return none
 */
void EEPROMWriteMedDiff(unsigned char value) {
	eeprom_update_byte(&eeprom.med_diff, value);
}













