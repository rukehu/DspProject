/*
 * sci.c
 *
 *  Created on: 2018年7月18日
 *      Author: Administrator
 */

#include <DSP2833x_Sci.h>
#include "sci.h"
#include "DSP28x_Project.h"
#include <string.h>
#include <stdio.h>


#define BUFF_MAX    256
uint8_t Tx_Buff[BUFF_MAX];
uint8_t Rx_Buff[BUFF_MAX];
static uint16_t txBuff_r = 0;
static uint16_t txBuff_w = 0;
static uint16_t rxBuff_r = 0;
static uint16_t rxBuff_w = 0;

interrupt void SciB_RxInterIsr(void);

void uart1_init(void)
{
    //InitScibGpio();
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;  //使能管脚内部上拉
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;

    //设置管脚量化控制寄存器
    GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 3;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;

    //开启管脚复用功能
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;

    EDIS;

    //通信控制寄存器
    SciaRegs.SCICCR.all = 0x0007;   //1停止位,无校验,8数据位
    SciaRegs.SCICTL1.all = 0x0003;  //屏蔽中断错误,初始化相关寄存器,发送和接收使能
    SciaRegs.SCICTL2.all = 0x0003;  //使能收发中断
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

#if CPU_FRQ_150MHZ
    SciaRegs.SCIHBAUD = 0x0001;
    SciaRegs.SCILBAUD = 0x00E7;
#endif
    ScicRegs.SCICTL1.all = 0x0023;

    ScibRegs.SCIFFRX.all = 0x0021;      //接收FIFO使能

    PieVectTable.SCIRXINTB = &SciB_RxInterIsr;
    IER |= M_INT9;
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;      //开启串口B接收中断 PIE Group 9, INT3
}

/**
 * @brief : 串口发送一个字符
 * @param : 发送的字符
 * @return:
 *      0 : 发送成功
 *      -1: 发送失败
 */
int8_t send_chr(uint8_t ch)
{
    int8_t err = 0;
    uint8_t cnt = 0;

    while(0 != SciaRegs.SCIFFTX.bit.TXFFST) {
        cnt++;
        if (cnt > 100) {
            err = -1;
            break;
        }
    }

    if (0 == err) {
        SciaRegs.SCITXBUF = ch;
    }

    return err;
}

/**
 * @brief : 串口发送字符串
 * @param :
 *    str : 发送的字符串头指针
 *    cnt : 发送字符串长度
 * @return:
 *      返回实际发送的字符长度
 */
uint16_t send_string(char *str, uint16_t cnt)
{
    uint16_t len = 0;
    uint16_t i = 0;

    for (i = 0; i < cnt; i++) {
        if (0 == send_chr(str[i])) {
            len++;
        }
    }

    return len;
}

/**
 * @brief : 读取发送缓冲字符
 * @param :
 * @return:
 *     成功 : 返回读取到的字符
 *     失败 : 返回0XFF
 *
 */
uint8_t txBuff_read_ch(void)
{
    uint8_t ch = 0xFF;

    if (txBuff_r != txBuff_w) {
        ch = Tx_Buff[txBuff_r];
        txBuff_r = (txBuff_r + 1) % BUFF_MAX;
    }

    return ch;
}

/**
 * @brief : 写入发送缓冲字符
 * @param :
 *     ch : 发送的字符
 * @return:
 *     成功 : 0
 *     失败 : -1
 *
 */
int8_t txBuff_write_ch(uint8_t ch)
{
    int8_t ret = 0;

    if ((txBuff_w + 1)%BUFF_MAX != txBuff_r) {
        Tx_Buff[txBuff_w] = ch;
        txBuff_w = (txBuff_w + 1) % BUFF_MAX;
    } else {
        ret = -1;
    }

    return ret;
}


/**
 * @brief : 读取发送缓冲字符
 * @param :
 * @return:
 *     成功 : 返回读取到的字符
 *     失败 : 返回0XFF
 *
 */
uint8_t rxBuff_read_ch(void)
{
    uint8_t ch = 0xFF;

    if (rxBuff_r != rxBuff_w) {
        ch = Rx_Buff[rxBuff_r];
        rxBuff_r = (rxBuff_r + 1) % BUFF_MAX;
    }

    return ch;
}

/**
 * @brief : 写入发送缓冲字符
 * @param :
 *     ch : 发送的字符
 * @return:
 *     成功 : 0
 *     失败 : -1
 *
 */
int8_t rxBuff_write_ch(uint8_t ch)
{
    int8_t ret = 0;

    if ((rxBuff_w + 1)%BUFF_MAX != rxBuff_r) {
        Rx_Buff[rxBuff_w] = ch;
        rxBuff_w = (rxBuff_w + 1) % BUFF_MAX;
    } else {
        ret = -1;
    }

    return ret;
}

interrupt void SciB_RxInterIsr(void)
{
    volatile uint8_t res;
    res = (ScibRegs.SCIRXBUF.bit.RXDT) & 0x00FF;

    rxBuff_write_ch(res);

    ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;    //清除标志位
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;    //清除中断位
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

void uart_test(void)
{
#if 0
    uint8_t ch;

    while ((ch = rxBuff_read_ch()) != 0xFF) {
        txBuff_write_ch(ch);
    }

    while ((ch = rxBuff_read_ch()) != 0xFF) {
        send_chr(ch);
    }
#endif
}


