/*
 * led.h
 *
 *  Created on: 2018Äê6ÔÂ4ÈÕ
 *      Author: Administrator
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include <stdint.h>
#include <DSP2833x_Gpio.h>
#include <DSP2833x_Device.h>

#define LED0 (GpioDataRegs.GPATOGGLE.bit.GPIO0)
#define LED1 (GpioDataRegs.GPATOGGLE.bit.GPIO1)
#define LED2 (GpioDataRegs.GPATOGGLE.bit.GPIO2)
#define LED3 (GpioDataRegs.GPATOGGLE.bit.GPIO3)
#define LED4 (GpioDataRegs.GPATOGGLE.bit.GPIO4)
#define LED5 (GpioDataRegs.GPATOGGLE.bit.GPIO5)
#define LED6 (GpioDataRegs.GPATOGGLE.bit.GPIO12)
#define LED7 (GpioDataRegs.GPBTOGGLE.bit.GPIO36)


void LedInit(void);
void LedTest(void);
void LedAllON(void);
void LedAllOff(void);

#endif /* INC_LED_H_ */
