/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "lcd.h"
#include "adc.h"
#include "init.h"
#include "screen.h"
#include "misc.h"
#include "timer.h"
#include "tempmeasure.h"
#include "trend.h"
#include "setup.h"
#include "remain.h"
#include "pump.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_DIR DDRA
#define LED_PORT PORTA
#define LED_PIN PA0

int main(void) {

	LED_DIR |= _BV(LED_PIN);

	Init();

	unsigned long int prev_time = 0;
	for (;;) {
		ScreenRefresh();

		ScreenSet_koll_temp(TempGet(NAPKOLLEKTOR_CH));
		ScreenSet_med_temp(TempGet(MEDENCE_CH));

		ScreenSet_trend(TrendGet());
		ScreenSet_trend_unit(TrendGetUnit());

		ScreenSet_on_temp(SetupGetOnTemp());

		ScreenSet_remain(RemainGet());
		ScreenSet_remain_unit(RemainGetUnit());

		PumpRefresh();
		ScreenSet_pump_state(PumpGetStatus());

		//LED villogtatás
		if(TimeGetNow() - prev_time > 50) {
			LED_PORT |= _BV(LED_PIN);
			prev_time = TimeGetNow();
		}
		_delay_ms(10);
		LED_PORT &= ~_BV(LED_PIN);
	}

	return 0;
}
