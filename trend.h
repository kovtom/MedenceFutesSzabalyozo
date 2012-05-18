/*!
 * \file trend.h
 * \brief Hőmérséklet emelkedési trend kiszámolása
 *
 * A napkollektorban a víz hőmérséklet emelkedésének nagyságát számolja
 * (MIN/SEC)/°C formában. Ha a számolt érték kisebb mint egy perc akkor
 * másodpercben adja vissza az adatot. Ha ez a trend több mint 99 perc
 * akkor is 99 percet ír ki.
 *
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#ifndef TREND_H_
#define TREND_H_

#define TREND_MAX 99 			//**< A trend érték maximuma */

/*!
 * \brief A trend változói tartalmazó struktúra
 */
typedef struct TREND {
	unsigned long int time_start;  	//**< trend mérés idejének kezdete */
	signed char temp_start;			//**< trend kezdeti hőmérséklet */
	unsigned int trend;				//**< számolt hőmérséket emelkedés idő/°C */
	unsigned char trend_unit;		//**< trend mértékegység (min/sec) */
}TREND;

void TrendInit(void);
void TrendClear(void);
unsigned char TrendGet(void);
unsigned char TrendGetUnit(void);

//debug miatt kell
unsigned long int TrendGetTimeStart(void);
signed char TrendGetTempStart(void);

#endif /* TREND_H_ */
