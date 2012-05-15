/*!
 * \file main.c
 *
 * \date Created on: 2012.05.11.
 * \author Author: Tamas Kovacs
 */

#include "init.h"
#include "lcd.h"
#include "strings.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define LED_DDR DDRA
#define LED_PORT PORTA
#define LED_PIN	PA0

volatile uint32_t time = 0;

ISR(TIMER0_OVF_vect) {
	static uint8_t counter;
	++time;
	if(counter == 50 ) {
		counter = 0;
	}
	if(counter < 47) {
		LED_PORT &= ~_BV(LED_PIN);
	} else {
		LED_PORT |= _BV(LED_PIN);
	}
	counter++;
}

int main(void) {

	//probahoz
	LED_DDR |= _BV(LED_PIN);
	char buffer[10];

	init();						//init RESET után

	lcd_clrscr();
	lcd_puts_p(StringPointers[s_Medence]);
	lcd_puts("21");
	lcd_put_CELSIUS;
	lcd_putc('\n');
	lcd_puts_p(StringPointers[s_Napkoll]);
	lcd_puts("18");
	lcd_put_min;
	_delay_ms(2000);

    lcd_clrscr();   /* clear display home cursor */

    lcd_puts("Copyright: ");


    lcd_gotoxy(0,1);
    for(uint8_t i = 0; i < DEFINED_CHAR; i++) {
    	lcd_putc(i);
    }
    _delay_ms(2000);
    lcd_clrscr();

    for (;;) {			//Loop...
		lcd_gotoxy(0,1);
		ltoa(time, buffer, 10);
		lcd_puts(buffer);
	}
	return 0;
}
