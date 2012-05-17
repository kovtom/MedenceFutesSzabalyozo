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

	unsigned char i = 40;
	for (;;) {
		ScreenRefresh();
		ScreenSet_koll_temp(GetTemp(NAPKOLLEKTOR_CH));
		_delay_ms(500);
		--i;
		if(i >= 0) ScreenSet_trend(i);
	}

	return 0;
}
