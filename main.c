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
#include "tempmeasure.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

int main(void) {

	Init();

	unsigned char i = 99;
	unsigned char j = 0;
	for (;;) {
		ScreenRefresh();
		ScreenSet_koll_temp(GetTemp(NAPKOLLEKTOR_CH));
		_delay_ms(100);
		if(i > 0) {
			--i;
		} else {
			i = 100;
		}
		ScreenSet_trend(i);
		if(j < 100) {
			++j;
		} else {
			j = 0;
		}
		ScreenSet_remain(j);
		ScreenSet_on_temp(j);
	}

	return 0;
}
