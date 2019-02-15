/*
 * watchDog.c
 *
 *  Created on: 2018��6��6��
 *      Author: Administrator
 */
#include "watchDog.h"

/**
* @brief :��ʼ�����Ź���Ĭ��״̬���Ź�δʹ��
* @param :Not
* @return:Not
*/
void WatchDogInit(void)
{
    EALLOW;
    SysCtrlRegs.SCSR &= ~BIT1;    //0�������Ź���λ�źţ�1�������Ź��ж��źţ��رտ��Ź���λ
    EDIS;

//    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;  //ʹ��PIE���ģ��
//    PieCtrlRegs.PIEIER1.bit.INTx8 = 1;  //ʹ�ܿ��Ź��ж�(��1���8�ж�)
    //IER &= ~M_INT1;     //0ʹ�ܿ��Ź���λ�źţ����Ź���λ�źźͿ��Ź��ж�1ֻ��ͬʱ����һ��(�ж�ʹ��ͨ�����ڵ͹��Ļ���)
    //EINT;               //�����ж�

}

void WatchDogeEnable(void)
{
    EALLOW;
    SysCtrlRegs.WDCR = 0x002E;  //WDDIS=0(ʹ�ܿ��Ź�����)WDCHK(101)WDPS(��Ƶ����)
    EDIS;
}

void FoodDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}


