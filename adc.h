/*!
 * \file adc.h
 * \brief Analog digital konverter deklarációk
 * \date Created on: 2012.05.15.
 * \author Author: Tamas Kovacs
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC0 0					//**< Analog channel 0 */
#define ADC1 1					//**< Analog channel 1 */
#define NAPKOLLEKTOR_CH	ADC1 	//**< Napkollektor szenzor ADC channel */
#define MEDENCE_CH ADC0			//**< Medence szenzor ADC channel */

void ADCInit(void);
unsigned int ADCGet(unsigned char);

#endif /* ADC_H_ */
