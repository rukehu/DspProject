/*
 * sci.h
 *
 *  Created on: 2018Äê7ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef INC_SCI_H_
#define INC_SCI_H_
#include <DSP2833x_Gpio.h>
#include <DSP2833x_Device.h>
#include "public.h"

void uart1_init(void);
int8_t send_chr(uint8_t ch);
void uart_test(void);


#endif /* INC_SCI_H_ */
