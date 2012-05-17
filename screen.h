/*!
 * \file screen.h
 * \brief Megjelenítés vezérlés
 *
 * Itt tároljuk az LCD-re kiírandó adatokat és vezéreljük az LCD-t.
 * Ezeken a rutinokon keresztül lehet elérni az LCD-t a program egyéb
 * részeiből.
 * Képernyőképek:
 * 		123456789012345678901234	<- LCD oszlopai
 * 1.	Medence:25C ^12mi/C S:BE 	<- Medence hőfok, hőm. emelkedés, szivattyú
 * 2.   Napkoll:34C R23mi  T:28C	<- Napkoll. hőfok, várható bekapcs., beállított hőm
 *
 * 1.	Utloso 5 felfutesi ido:
 * 2.	123,123,123,123,123 perc
 *
 * 1.	Beallitasok(1):
 * 2.	Bekapcs. mod:<abszolut>
 *                   <kulonbseg>
 *
 * 1.	Beallitasok(2):
 * 2.	Bekapcs. hofok: ^20Cˇ
 *
 * A fenti értékeket egy struktúrában tároljuk és az alább definiált
 * függvényeken keresztül érhetőek el ill. módosíthatóak.
 *
 * \date Created on: 2012.05.16.
 * \author Author: Tamas Kovacs
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#define MEDENCE 0		//**< 'Medence:' string */
#define NAPKOLL 1		//**< 'Napkoll:' string */
#define UTOLSO_5 2		//**< 'Utolso 5 felfutesi ido:' string */
#define PERC 3			//**< 'perc' string */
#define BEALLITASOK 4	//**< 'Beallitasok' string */
#define BEKAPCSMOD 5	//**< 'Bekapcs. mod:' string */
#define ABSZOLUT 6		//**< '<abszolut>' string */
#define KULONBSEG 7 	//**< '<kulonbseg>' string */
#define BEKAPCSHOF 8	//**< 'Bekapcs. hofok:' string */
#define B1 9			//**< '(1):' string */
#define B2 10			//**< '(2):' string */
#define ERROR_S 11		//**< 'Error' string */
#define BE_S 12			//**< 'BE\n' string */
#define KI_S 13			//**< 'KI\n' string */
#define PUPM_STATE_S 14	//**< 'S:' string */
#define REMAIN_S 15		//**< 'R:' string */
#define ON_TEMP_S 16	//**< 'T:' string */

#define DEFINED_CHAR 8	//**< Ennyi saját LCD karaktert definiálunk */

#define TREND_MAX 99 	//**< A trend érték maximuma */
#define REMAIN_MAX 99	//**< A remain érték maximuma */
#define ONTEMP_MAX 99	//**< Az on_temp érték maximuma */

/*!
 * \struct SCREEN
 * \brief LCD screen struktúra
 *
 * Ebben tároljuk az LCD-re kiírandó adatokat
 */
typedef struct SCREEN {
	unsigned char med_temp;		//**< Medence hőmérséklet string */
	unsigned char koll_temp;	//**< Napkollektor hőmérséklet */
	unsigned char trend;		//**< Hőmérséklet emelkedés perc/sec /°C */
	unsigned char trend_unit;	//**< Hőm. emelkedés mértékegység (sec/min) */
	unsigned char pump_state;	//**< Szivattyú státusz (BE/KI)
	unsigned char remain;		//**< Várható bekapcsolási idő (sec/min) */
	unsigned char remain_unit;	//**< Várható felfűtés mértékegység */
	unsigned char on_temp;		//**< Bekapcsolási hőfok */
	unsigned char last_heat[5];	//**< Utolsó öt felfűtési időtartam */
	unsigned char mode;			//**< Bekapcsolási metódus (különbségi/abszolút) */
	unsigned char selector;		//**< Melyik képernyőt jelenítjük meg(0,1,3,4) */
	unsigned char prev_selector;//**< Az előző refresh selectora */
} SCREEN;

void ScreenInit(void);
void ScreenSelector(unsigned char);
void ScreenRefresh(void);
void ScreenSet_med_temp(unsigned char);
void ScreenSet_koll_temp(unsigned char);
void ScreenSet_trend(unsigned char);
void ScreenSet_trend_unit(unsigned char);
void ScreenSet_pump_state(unsigned char);
void ScreenSet_remain(unsigned char);
void ScreenSet_remain_unit(unsigned char);
void ScreenSet_on_temp(unsigned char);
void ScreenSet_last_heat(unsigned char *);
void ScreenSet_mode(unsigned char);

#endif /* SCREEN_H_ */
