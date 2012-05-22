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

#define MEDENCE_S 0		//**< 'Medence:' string */
#define NAPKOLL_S 1		//**< 'Napkoll:' string */
#define UTOLSO_5_S 2		//**< 'Utolso 5 felfutesi ido:' string */
#define PERC_S 3			//**< 'perc' string */
#define BEALLITASOK_S 4	//**< 'Beallitasok' string */
#define BEKAPCSMOD_S 5	//**< 'Bekapcs. mod:' string */
#define ABSZOLUT_S 6		//**< '<abszolut>' string */
#define KULONBSEG_S 7 	//**< '<kulonbseg>' string */
#define BEKAPCSHOF_S 8	//**< 'Bekapcs. hofok:' string */
#define B1_S 9			//**< '(1):' string */
#define B2_S 10			//**< '(2):' string */
#define ERROR_S 11		//**< 'Error' string */
#define BE_S 12			//**< 'BE\n' string */
#define KI_S 13			//**< 'KI\n' string */
#define PUPM_STATE_S 14	//**< 'S:' string */
#define REMAIN_S 15		//**< 'R:' string */
#define ON_TEMP_ABS_S 16 //**< 'T=' string */
#define PUMP_ERROR_S 17 //**< '**\n' string */
#define ON_TEMP_KUL_S 18 //**< 'T>' string */
#define ALL_TIME_S 19 	//**< 'Szivattyú össz. üzemidő:\n' string */
#define DAY_S 20		//**< 'd  ' string */
#define HOUR_S 21		//**< 'h  ' string */
#define SETUP_SAVED_CLEAR_S 22 //**< 'Mentett adatok torlese:\n Ossz. uzem/Utolso felf.' */
#define B3_S 23			//**< '(3):' string */
#define B4_S 24			//**< '(4):' string */
#define KOLL_KORR_S 25	//**< 'Napkoll.kalibr:' */
#define MED_KORR_S 26	//**< 'Medence.kalibr:' */

#define SELECTOR_MAX 5	//**< Ennyi screen-ünk van */

#define DEFINED_CHAR 8	//**< Ennyi saját LCD karaktert definiálunk */

#define ONTEMP_MAX 99	//**< Az on_temp érték maximuma */
#define MED_TEMP_MAX 99 //**< A medence hőmérséklet maximuma */
#define NAPKOLL_TEMP_MAX 99 /**< A napkollektor hőmérséklet maximuma */

/*!
 * \struct SCREEN
 * \brief LCD screen struktúra
 *
 * Ebben tároljuk az LCD-re kiírandó adatokat
 */
typedef struct SCREEN {
	unsigned char selector;		//**< Melyik képernyőt jelenítjük meg(0,1,3,4) */
	unsigned char prev_selector;//**< Az előző refresh selectora */
} SCREEN;

void ScreenInit(void);
void ScreenSelector(unsigned char);
void ScreenNextSelector(void);
unsigned char ScreenGetSelector(void);
void ScreenRefresh(void);

#endif /* SCREEN_H_ */
