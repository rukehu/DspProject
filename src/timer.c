/*
 * timer.c
 *
 *  Created on: 2018Äê6ÔÂ10ÈÕ
 *      Author: Administrator
 */
#include "timer.h"
#include "DSP2833x_CpuTimers.h"
#include "DSP2833x_Examples.h"
#include "led.h"


interrupt void cpu_timer0_isr(void);

void timer0Init(void)
{
    EALLOW;
    PieVectTable.TINT0 = &cpu_timer0_isr;
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000000);
    CpuTimer0Regs.TCR.all = 0x4001;

    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    EINT;
    ERTM;
}

interrupt void cpu_timer0_isr(void)
{
    CpuTimer0.InterruptCount++;

    LedTest();

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}



