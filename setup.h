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

typedef struct SETUP {
	unsigned char setup_valid_mode;		//**< abszolút/különbségi */
	unsigned char setup_valid_on_temp;	//**< bekapcsolási hőmérséklet */
	unsigned char setup_tmp_mode;	//**< ez állítjuk a setupban, ha valid akkor mentjük abszolút/különbségi */
	unsigned char setup_tmp_on_temp;//**< ez állítjuk a setupban, ha valid akkor mentjük bekapcsolási hőmérséklet */
}SETUP;

void SetupInit(void);
unsigned char SetupGetMode(void);
unsigned char SetupGetOnTemp(void);
unsigned char SetupGetTmpMode(void);
unsigned char SetupGetTmpOnTemp(void);
void SetupWriteOnTemp(void);
void SetupWriteMode(void);
void SetupWriteTmpOnTemp(unsigned char);
void SetupWriteTmpMode(unsigned char);
void SetupUndo(void);

#endif /* SETUP_H_ */
