/*
 * timer.h
 *
 *  Created on: 2018Äê6ÔÂ10ÈÕ
 *      Author: Administrator
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include <stdint.h>

#define delay_us(n) DELAY_US(n)
#define delay_ms(m) DELAY_US(1000 * m)

void timer0Init(void);

#endif /* INC_TIMER_H_ */
