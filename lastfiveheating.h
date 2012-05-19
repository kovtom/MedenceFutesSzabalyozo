/*!
 * \file lastfiveheating.h
 * \brief Utolsó öt felfűtés.
 *
 * Az utlsó öt felfűtést értékeli ki.
 *
 * \date Created on: 2012.05.19.
 * \author Author: tomi
 */

#ifndef LASTFIVEHEATING_H_
#define LASTFIVEHEATING_H_

#define LASTHEAT_MAX 999	//**< A maximum értéke a felfűtési időnek */

typedef struct LASTHEATING {
	unsigned char prev_pump_state;	//**< tároljuk a kiértékeléshez */
	unsigned long int prev_time;	//**< előző time a kiértékeléshez */
	unsigned char measure_status;	//**< mérés közben vagyunk vagy sem */
	unsigned int heating_time[5];	//**< utolsó öt felfűtési idő */
}LASTHEATING;

void LastHeatingInit(void);
void LastHeatingRefresh(void);
void LastHeatingGet(unsigned int *);

#endif /* LASTFIVEHEATING_H_ */
