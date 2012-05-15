/*!
 * \file init.h
 * \brief Reset utáni inicializálás
 *
 * Inicializálás reset után:
 * 1. Különböző adatok feltöltése az EEPROM-ból.
 * 2. ADC inicializálása.
 * 3. LCD inicializálása.
 * 4. Saját karakterek definiciója
 * 4. Timer inicializálása.
 * 5. Mérünk egy napkollektor hőmérsékletet a kezdéshez.
 * 6. Mérünk egy medence hőmérsékletet a kezdéshez.
 * Az 6-5 pont azért kell, hogy legyen previous adataink a különböző
 * funkciókhoz, melyek ezt felhasználják.
 * 7. Tároljuk az 5-6 -os eredményeket a megfelelő adat struktúrákba.
 *
 * A setup során az egyes lépéseket kiírjuk a kijelzőre, egy kis
 * késleltetéssel, hogy látható legyen a boot ill. init folyamat.
 *
 * \date Created on: 2012.05.13.
 * \author Author: kovacst
 */
#include <avr/pgmspace.h>

#ifndef INIT_H_
#define INIT_H_

#define DEFINED_CHAR 7

/*!
 * \brief Saját karakterek.
 *
 * min, sec, °C, fel háromszög, le háromszög+
 */
static const PROGMEM unsigned char defChar[] = {
		0x00, 0x00, 0x1a, 0x15, 0x15, 0x15, 0x15, 0x00,		//min
		0x00, 0x00, 0x16, 0x05, 0x15, 0x15, 0x15, 0x00,
		0x00, 0x00, 0x03, 0x04, 0x02, 0x01, 0x06, 0x00,		//sec
		0x00, 0x00, 0x19, 0x12, 0x1a, 0x12, 0x19, 0x00,
		0x18, 0x1b, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00,		//°C
		0x00, 0x04, 0x04, 0x0e, 0x0e, 0x1f, 0x1f, 0x00,		//fel
		0x00, 0x1f, 0x1f, 0x0e, 0x0e, 0x04, 0x04, 0x00		//le
};

void init(void);
void EEPROMtoDatas(void);
void init_ADC(void);
void init_LCD(void);
void defineChars(void);
void init_Timer(void);

#endif /* INIT_H_ */
