/*
 * \file tempmeasure.h
 * \brief Napkollektor hőmérséklete
 *
 * \date Created on: 2012.05.16.
 * \author Author: tomi
 */

#ifndef TEMPMEASURE_H_
#define TEMPMEASURE_H_

#define AVERAGE_COUNT 50		//**< Ennyi mérést végzünk egyszerre, majd átlagolunk */

unsigned char GetTemp(unsigned char channel);

#endif /* TEMPMEASURE_H_ */
