/*!
 * \file init.h
 * \brief Reset utáni inicializálás
 *
 * Inicializálás reset után:
 * 1. Különböző adatok feltöltése az EEPROM-ból.
 * 2. ADC inicializálása.
 * 3. LCD inicializálása.
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

#ifndef INIT_H_
#define INIT_H_

void init(void);
void EEPROMtoDatas(void);
void init_ADC(void);
void init_LCD(void);

#endif /* INIT_H_ */
