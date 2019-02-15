/*
 * watchDog.c
 *
 *  Created on: 2018年6月6日
 *      Author: Administrator
 */
#include "watchDog.h"

/**
* @brief :初始化看门狗，默认状态看门狗未使能
* @param :Not
* @return:Not
*/
void WatchDogInit(void)
{
    EALLOW;
    SysCtrlRegs.SCSR &= ~BIT1;    //0开启看门狗复位信号，1启动看门狗中断信号，关闭看门狗复位
    EDIS;

//    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;  //使能PIE相关模块
//    PieCtrlRegs.PIEIER1.bit.INTx8 = 1;  //使能看门狗中断(第1组第8中断)
    //IER &= ~M_INT1;     //0使能看门狗复位信号，看门狗复位信号和看门狗中断1只能同时开启一个(中断使能通常用于低功耗唤醒)
    //EINT;               //开总中断

}

void WatchDogeEnable(void)
{
    EALLOW;
    SysCtrlRegs.WDCR = 0x002E;  //WDDIS=0(使能看门狗功能)WDCHK(101)WDPS(分频设置)
    EDIS;
}

void FoodDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}


