/*!
 * \file strings.h
 * \brief Szavak definiciója
 *
 * Szavak melyeket a program memóriában tárolunk
 *
 * \date Created on: 2012.05.14.
 * \author Author: tomi
 */

#ifndef STRINGS_H_
#define STRINGS_H_

#include <avr/pgmspace.h>

#define s_Medence 0
#define s_Napkoll 1
#define lcd_put_CELSIUS lcd_putc(4)
#define lcd_put_min lcd_putc(0);lcd_putc(1)

const PROGMEM char String1[] = "Medence:";
const PROGMEM char String2[] = "Napkoll:";

const char * StringPointers[] = {
		String1,
		String2
};


#endif /* STRINGS_H_ */
