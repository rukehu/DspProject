/*
 * app.c
 *
 *  Created on: 2018Äê6ÔÂ5ÈÕ
 *      Author: Administrator
 */
#include <stdint.h>
#include "app.h"
#include "led.h"
#include "watchDog.h"
#include "timer.h"
#include "key.h"
#include "sci.h"


void AppDelay(uint32_t time)
{
    int i;

    while (time--) {
        i = 500;
        while (i--);
    }

}

void AppInit(void)
{

    LedInit();
    //WatchDogInit();
    //timer0Init();
    //key_init();
    //uart1_init();

}

void AppProcess(void)
{
    //WatchDogeEnable();
    while (1)
    {
        //FoodDog();
        AppDelay(5000);
        //LED0 = ~LED0;
        //key_test();
        uart_test();
        //send_chr('H');
    }

}



