/*
 * \file setup.h
 * \brief Setup funkció
 *
 * Ezek a függvények adják vissza a beállított adatokat, mint bekapcsolási
 * hőmérséklet stb...
 *
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#ifndef SETUP_H_
#define SETUP_H_

#define WRITE_TO_RAM	0			//**< Ezzel jelezzük, ha csak RAM-ba mentünk */
#define WRITE_TO_EEPROM 1			//**< Ezzel jelezzük, hogy EEPROM-ba mentünk */

typedef struct SETUP {
	unsigned char valid_mode;		//**< abszolút/különbségi */
	unsigned char valid_on_temp;	//**< bekapcsolási hőmérséklet */
	unsigned char tmp_mode;			//**< ez állítjuk a setupban, ha valid akkor mentjük abszolút/különbségi */
	unsigned char tmp_on_temp;		//**< ez állítjuk a setupban, ha valid akkor mentjük bekapcsolási hőmérséklet */
	signed char koll_diff; 			//**< koll. szenzor korrekció */
	signed char med_diff;			//**< medence szenzor korrekció */
}SETUP;

void SetupInit(void);
unsigned char SetupGetMode(void);
unsigned char SetupGetTmpMode(void);
unsigned char SetupGetOnTemp(void);
unsigned char SetupGetTmpOnTemp(void);
signed char SetupGetKollDiff(void);
signed char SetupGetMedDiff(void);
void SetupWriteOnTemp(void);
void SetupWriteTmpOnTemp(unsigned char);
void SetupWriteMode(void);
void SetupWriteTmpMode(unsigned char);
void SetupWriteKollDiff(signed char, unsigned char);
void SetupWriteMedDiff(signed char, unsigned char);
void SetupUndo(void);

#endif /* SETUP_H_ */
