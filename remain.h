/*!
 * \file remain.h
 * \brief Várható bekapcsolási időpont
 *
 * A modul kiszámolja, hogy mennyi idő van még a szivattyú bekapcsolásáig.
 *
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#ifndef REMAIN_H_
#define REMAIN_H_

#define REMAIN_MAX 99	//**< A remain érték maximuma */

typedef struct REMAIN {
	unsigned int remain;			//**< ennyi idő van még */
	unsigned char remain_unit;	//**< remain mértékegysége */
}REMAIN;

void RemainInit(void);
unsigned char RemainGet(void);
unsigned char RemainGetUnit(void);

#endif /* REMAIN_H_ */
