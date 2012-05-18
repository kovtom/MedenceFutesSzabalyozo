/*!
 * \file tempmeasure.h
 * \brief Napkollektor hőmérséklete
 *
 * \date Created on: 2012.05.16.
 * \author Author: tomi
 */

#ifndef TEMPMEASURE_H_
#define TEMPMEASURE_H_

#define ADC0 0					//**< Analog channel 0 */
#define ADC1 1					//**< Analog channel 1 */
#define NAPKOLLEKTOR_CH	ADC1 	//**< Napkollektor szenzor ADC channel */
#define MEDENCE_CH ADC0			//**< Medence szenzor ADC channel */
#define AVERAGE_COUNT 50		//**< Ennyi mérést végzünk egyszerre, majd átlagolunk */

unsigned char TempGet(unsigned char channel);

#endif /* TEMPMEASURE_H_ */
