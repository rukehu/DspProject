/*
 * led.c
 *
 *  Created on: 2018年6月4日
 *      Author: Administrator
 */
#include "led.h"


void LedInit(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all &= ~0x103F;  //将gpio0设置为通用IO
    GpioCtrlRegs.GPADIR.all |= 0x103F;    //将A组的(0~5)号管脚设置为输出模式

    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO36 = 1;

    EDIS;

    LedAllOff();
}

void LedDelay(uint32_t tim)
{
    while (tim--);

}

void LedTest(void)
{
    //GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;   //翻转IO口
    LED0 = ~LED0;
    LedDelay(655350);
    LED1 = ~LED1;
    LedDelay(655350);
    LED2 = ~LED2;
    LedDelay(655350);
    LED3 = ~LED3;
    LedDelay(655350);
    LED4 = ~LED4;
    LedDelay(655350);
    LED5 = ~LED5;
    LedDelay(655350);
    LED6 = ~LED6;
    LedDelay(655350);
    LED7 = ~LED7;
}

void LedAllOff(void)
{
    //GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;   //翻转IO口
    LED0 = 1;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    LED7 = 1;
}

void LedAllON(void)
{
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
}


