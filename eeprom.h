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
	unsigned int last_five[5];	//**< utolsó öt felfűtési idő */
	unsigned long int total_pump_time; //**< összes szivattyú üzemidő */
	unsigned char koll_diff;		//**< Napkollektor szenzor korrekció */
	unsigned char med_diff;		//**< Medence szenzor korrekció */
}EEPROM_S;

unsigned char EEPROMReadMode(void);
unsigned char EEPROMReadOnTemp(void);
void EEPROMReadLastFive(unsigned int *);
unsigned long int EEPROMReadTotalPumpTime(void);
unsigned char EEPROMReadKollDiff(void);
unsigned char EEPROMReadMedDiff(void);
void EEPROMWriteMode(unsigned char);
void EEPROMWriteOnTemp(unsigned char);
void EEPROMWriteLastFive(unsigned int *);
void EEPROMWriteTotalPumpTime(unsigned long int);
void EEPROMWriteKollDiff(unsigned char);
void EEPROMWriteMedDiff(unsigned char);

#endif /* EEPROM_H_ */
