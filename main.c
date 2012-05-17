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
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

int main(void) {

	Init();

	for (;;) {
		static unsigned char i;
		ScreenRefresh();
		ScreenSelector(i);
		_delay_ms(4000);
		i++;
		if(i > 3) i = 0;
	}

	return 0;
}
