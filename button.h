/*!
 * \file button.h
 * \brief Nyomogombokat kezelő függvények
 * \date Created on: 2012.05.20.
 * \author Author: tomi
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#define BUTTON_PORT 		PORTC			//**< Nyomógombok PORTx regiszter */
#define BUTTON_PIN			PINC			//**< Nyomógombok PINx regiszter */
#define BUTTON_MENU_PORT	BUTTON_PORT		//**< MENU port */
#define BUTTON_UP_PORT		BUTTON_PORT		//**< UP port */
#define BUTTON_DOWN_PORT 	BUTTON_PORT		//**< DOWN port */
#define BUTTON_OK_PORT		PORTD			//**< OK port */
#define BUTTON_MENU_PIN 	BUTTON_PIN		//**< MENU PINx reg. */
#define BUTTON_UP_PIN 		BUTTON_PIN		//**< UP PINx reg. */
#define BUTTON_DOWN_PIN 	BUTTON_PIN		//**< DOW PINx reg. */
#define BUTTON_OK_PIN		PIND			//**< OK PINx reg */
#define BUTTON_MENU			6				//**< MENU pin */
#define BUTTON_UP			1				//**< UP pin */
#define BUTTON_DOWN			0				//**< DOWN pin */
#define BUTTON_OK			7				//**< OK pin */
#define INT0_PORT			PORTD			//**< INT0 port */
#define INT0_PIN			2				//**< INT0 pin */

#define B_MENU				1				//**< MENU értéke a button-ban */
#define B_UP				2				//**< UP értéke a button-ban */
#define B_DOWN				4				//**< DOWN értéke a button-ban */
#define B_OK				8				//**< OK értéke a button-ban */
#define MENU_TIMEOUT		500				//**< /50 másodperc a timeout */

/*!
 * \brief Nyomógombok állapotát tároló struktúra.
 */
typedef struct BUTTON {
	unsigned char button;		 //**< Nyomógombok állapota BIT0 = BUTTON_MENU stb... */
	unsigned long int prev_prell_time; //**< Előző kiértékelés ideje, prellegés miatt */
	unsigned long int prev_menu_time; //**< Menü timeout miatt */
}BUTTON;

void ButtonInit(void);
unsigned char ButtonGet(void);
void ButtonMenu(void);

#endif /* BUTTON_H_ */
