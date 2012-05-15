/*!
 * \file adc.c
 * \brief Analog digital konverter függvények
 * \date Created on: 2012.05.15.
 * \author Author: Tamas Kovacs
 */

#include <avr/io.h>

/*!
 * \brief ADC inicializálása
 *
 * ADMUX = Vcc mint referencia, AREF lábon kondi <REFS0<-1>.
 * ADCSRA = 'ADEN' ADC engedélyezése, <ADPS2:0> ADC előosztás beállítása.
 * Ennek az értéknek (F_CPU/előosztás) 50-200 KHz között kell lennie.
 *
 * \param void
 * \return none
 */
void ADCInit(void) {
	           ADMUX |= (1<<REFS0);    			// Vcc mint referencia
	           ADCSRA = (1<<ADEN)  |
	        		    (1<<ADPS2) | (1<<ADPS1);// ADC engedelyezese, ADC eloosztas = 64 (62.5 KHz)
}

/*!
 * \brief ADC kiolvasása
 *
 * A függvény visszaadja a beolvasott csatorna 10bit-es értékét.
 *
 * \param channel unsigned char channel
 * \return ADCW unsigned int ADCW (10bit)
 */
unsigned int ADCGet(unsigned char channel) {
	ADMUX = (ADMUX & 0b11110000) | channel;    	// ADC csatorna kivalasztasa
	ADCSRA |= (1<<ADSC);    					// ADC konverzio elinditasa
	while (ADCSRA & (1<<ADSC));    				// adat érvényessége? Az első adatot nem használjuk fel.
	ADCSRA |= (1<<ADSC);         				// ADC konverzió elindítása
	while (ADCSRA & (1<<ADSC));    				// adat érvényes?
	return (ADCW);    							// ADC ertek kiolvasása ill. visszaadása
}
