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
	unsigned char setup_mode;		//**< abszolút/különbségi */
	unsigned char steup_on_temp;	//**< bekapcsolási hőmérséklet */
}SETUP;

void SetupInit(void);
unsigned char SetupGetMode(void);
unsigned char SetupGetOnTemp(void);

#endif /* SETUP_H_ */
