/*!
 * \file trend.c
 * \brief Hőmérséklet emelkedést számoló  függvények.
 * \date Created on: 2012.05.18.
 * \author Author: tomi
 */

#include "misc.h"
#include "trend.h"
#include "timer.h"
#include "tempmeasure.h"

static TREND trend;

#ifdef DEBUG
unsigned long int TrendGetTimeStart(void) {
	return trend.time_start;
}

signed char TrendGetTempStart(void) {
	return trend.temp_start;
}
#endif

/*!
 * \brief Hőmérséklet emelkedési trend inicializálása
 * \param void
 * \return none
 */
void TrendInit(void) {
	TrendClear();
}

/*!
 * \brief Hőmérséklet emelkedési trend nullázása.
 * \param void
 * \return none
 */
void TrendClear(void) {
	trend.time_start = TimeGetNow();
	trend.temp_start = (signed char)TempGet(NAPKOLLEKTOR_CH);
}

/*!
 * \brief Hőmérséklet emelkedési trend számolása funkció.
 * \param void
 * \return trend.trend unsigned char
 */
unsigned char TrendGet(void) {
	unsigned long int time = TimeGetNow();
	unsigned long int delta_time = (time - trend.time_start) / TICK_SEC;
	signed char delta_temp = TempGet(NAPKOLLEKTOR_CH) - trend.temp_start;
	if(delta_temp > 0) {
		trend.trend = delta_time / delta_temp;
		if(trend.trend > 59) {
			trend.trend = trend.trend / 60;
			trend.trend_unit = MIN;
		} else {
			trend.trend_unit = SEC;
		}
	} else {
		trend.trend = TREND_MAX;
		trend.trend_unit = MIN;
	}
	return (unsigned char)trend.trend;
}

/*!
 * \brief Hőmérséklet emelkedési trend mértékegysége
 * \param void
 * \return trend.trend_unit unsigned char
 */
unsigned char TrendGetUnit(void) {
	return trend.trend_unit;
}
