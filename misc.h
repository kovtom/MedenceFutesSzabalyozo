/*
 * \file misc.h
 * \brief Különféle állandók definiciója
 * \date Created on: 2012.05.16.
 * \author Author: Tamas Kovacs
 */

#ifndef MISC_H_
#define MISC_H_

#define DEBUG_TEMPMEASURE
#define SCREEN_MAIN 0		//**< A fő képernyő */
#define SCREEN_LASTFIVE 1	//**< Utolsó öt felfűtési idő képernyő */
#define SCREEN_SET_MODE 2	//**< Beállítás fűtési mód képernyő */
#define SCREEN_SET_TEMP 3	//**< Beállítás hőmérséklet képernyő */
#define PUMP_OFF 0			//**< OFF (szivattyú) */
#define PUMP_ON 1			//**< ON (szivattyú) */
#define PUMP_ERROR 3		//**< Magasabb a medence hőm mint az abs beállított */
#define MODE_ABS 1			//**< Bekapcsolási módszer <abszolut> */
#define MODE_KUL 0			//**< Bekapcsolási módszer <kulonbseg> */
#define MIN 1				//**< min mértékegység */
#define SEC 0				//**< sec mértékegység */

#define MIN_C1 0			//**< min karakter első része */
#define MIN_C2 1			//**< min karakter második része */
#define SEC_C1 2			//**< sec karakter első része */
#define SEC_C2 3			//**< sec karakter második része */
#define CELSIUS_C 4			//**< °C karakter */
#define FEL_C 5				//**< ^ karakter */
#define LE_C 6				//**< ˇ karakter */
#define FELNYIL 7			//**< felfelé mutató nyíl karakter */

#define LCD_PUTS_MIN lcd_putc(MIN_C1);lcd_putc(MIN_C2)  //**< min mértékegység kiírása */
#define LCD_PUTS_SEC lcd_putc(SEC_C1);lcd_putc(SEC_C2)	//**< sec mértékegység kiírása */

#endif /* MISC_H_ */
