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
#include "lastfiveheating.h"
#include "button.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_DIR DDRA
#define LED_PORT PORTA
#define LED PA0

int main(void) {

	LED_DIR |= _BV(LED); //LED init

	Init();

	for (;;) {
		static unsigned long int prev_time;
		static unsigned char visit_led;
		static unsigned char led_status;

		ScreenRefresh();
		PumpRefresh();
		LastHeatingRefresh();
		ButtonMenu();

		//LED villogtatás
		if(TimeGetNow() - prev_time > visit_led) {
			if(led_status) {
				LED_PORT |= _BV(LED);
				visit_led = 1;
			} else {
				LED_PORT &= ~_BV(LED);
				visit_led = 49;
			}
			prev_time =TimeGetNow();
			led_status = !led_status;
		}
	}
	return 0;
}
