/*!
 * \file eeprom.h
 * \brief EEPROM-ban tárolt adatok olvasása írása
 * \date Created on: 2012.05.19.
 * \author Author: Tamas Kovacs
 */

#ifndef EEPROM_H_
#define EEPROM_H_

typedef struct EEPROM_S {
	unsigned char mode;			//**< bekapcsolási metódus */
	unsigned char on_temp;		//**< bekapcsolási hőmérséklet */
	unsigned char last_five[5];	//**< utolsó öt felfűtési idő */
	unsigned long int total_pump_time; //**< összes szivattyú üzemidő */
}EEPROM_S;

void EEPROMInit(void);
unsigned char EEPROMReadMode(void);
unsigned char EEPROMReadOnTemp(void);
void EEPROMReadLastFive(unsigned char *);
unsigned long int EEPROMReadTotalPumpTime(void);

void EEPROMWriteMode(unsigned char);
void EEPROMWriteOnTemp(unsigned char);
void EEPROMWriteLastFive(unsigned char *);
void EEPROMWriteTotalPumpTime(unsigned long int);

#endif /* EEPROM_H_ */
