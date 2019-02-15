/*
 * key.h
 *
 *  Created on: 2018Äê6ÔÂ13ÈÕ
 *      Author: Administrator
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_
#include <stdint.h>
#include <DSP2833x_Gpio.h>
#include <DSP2833x_Device.h>
#include "DSP2833x_Examples.h"

#define SCAN_KEY_LIST_0     (GpioDataRegs.GPBDAT.bit.GPIO50)
#define SCAN_KEY_LIST_1     (GpioDataRegs.GPBDAT.bit.GPIO49)
#define SCAN_KEY_LIST_2     (GpioDataRegs.GPBDAT.bit.GPIO48)
#define SCAN_KEY_CLER       (GpioDataRegs.GPBDAT.all &= ~0x070000)
#define KEY_DATA_REG        ((GpioDataRegs.GPBDAT.all & 0x380000) >> 16)

void key_init(void);
int16_t key_check(void);
void key_test(void);
#endif /* INC_KEY_H_ */
