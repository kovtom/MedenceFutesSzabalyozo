/*!
 * \file timer.h
 * \brief Időmérés
 *
 * 20msec-es tick interruptból, mellyel egy 32 bites számlálót folyamatosan növelünk.
 * A számláló így 994 nap után túlcsordul, de ez megfelelően hosszú idő. A 20ms-et 256-os
 * osztóval adódik 3,2768 MHz-es órajellel.
 *
 * \date Created on: 2012.05.18.
 * \author Author: Tamas Kovacs
 */

#ifndef TIMER_H_
#define TIMER_H_

#define PRESCALER_1    (1<<CS00)					//**< clk/(No prescaling) */
#define PRESCALER_8	   (1<<CS01)					//**< clk/8	*/
#define PRESCALER_64   ((1<<CS01)|(1<<CS00))		//**< clk/64 */
#define PRESCALER_256  (1<<CS02)					//**< clk/256 */
#define PRESCALER_1024 ((1<<CS02)|(CS01))			//**< clk/1024 */
#define TICK_SEC 50									//**< ennyi tick/sec */
void TimerInit(void);
unsigned long int TimeGetNow(void);

#endif /* TIMER_H_ */
