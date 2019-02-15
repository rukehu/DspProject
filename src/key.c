/*
 * key.c
 *
 *  Created on: 2018��6��13��
 *      Author: Administrator
 */
#include "key.h"
#include "timer.h"
#include "led.h"

void key_init(void)
{
    EALLOW;

    GpioCtrlRegs.GPBMUX2.all &= ~0x3F;      //ͨ��IO
    GpioCtrlRegs.GPBDIR.all &= ~0x38;        //gpio51~53����Ϊ����ģʽ��ɨ��
    GpioCtrlRegs.GPBDIR.all |= 0x070000;    //gpio48~50����Ϊ���ģʽ��ɨ��
    SCAN_KEY_CLER;                           //gpio48~50����Ϊ����͵�ƽ

    EDIS;
}

void keyDelay(uint32_t tim)
{
    while (tim--);
}


/**
 * @brief :����ȥ����
 * @param :Not
 * @return:
 *      0:�а������£�����ֵ��������
 */
uint16_t to_shake()
{
    keyDelay(1000000);

    if (KEY_DATA_REG != 0x38)
        return 0;

    return 1;
}

/**
 * @brief :ɨ���Ƿ���ڰ�������
 * @param :Not
 * @return:
 *      ����0:��ʾ���°����ı��
 *      0   :û�а�������
 */
int16_t key_check(void)
{
    uint16_t key_val;
    uint16_t key_num = 0;

    key_val = KEY_DATA_REG;

    if (key_val != 0x38) {

        if (0 != to_shake())
            return 0;

        SCAN_KEY_LIST_0 = 1;    //ɨ���0�а����Ƿ��а�������
        keyDelay(1000000);
        if (key_val != KEY_DATA_REG) {
            switch (key_val) {
                case 0x18:
                    key_num = 1;
                    break;
                case 0x28:
                    key_num = 4;
                    break;
                case 0x30:
                    key_num = 7;
                    break;
            }
            goto key_flag;
        }

        SCAN_KEY_LIST_1 = 1;    //ɨ���1�а����Ƿ��а�������
        keyDelay(1000000);
        if (key_val != KEY_DATA_REG) {
            switch (key_val) {
                case 0x18:
                    key_num = 2;
                    break;
                case 0x28:
                    key_num = 5;
                    break;
                case 0x30:
                    key_num = 8;
                    break;
            }
            goto key_flag;
        }

        SCAN_KEY_LIST_2 = 1;    //ɨ���2�а����Ƿ��а�������
        keyDelay(1000000);
        if (key_val != KEY_DATA_REG) {
            switch (key_val) {
                case 0x18:
                    key_num = 3;
                    break;
                case 0x28:
                    key_num = 6;
                    break;
                case 0x30:
                    key_num = 9;
                    break;
            }
            goto key_flag;
        }
    }

key_flag:
    SCAN_KEY_CLER;
    return key_num;
}


void key_test(void)
{
    uint16_t key;
    key = key_check();
    switch (key) {
    case 1:
            LED0 = ~LED0;
            break;
    case 2:
            LED1 = ~LED1;
            break;
    case 3:
            LED2 = ~LED2;
            break;
    case 4:
            LED3 = ~LED3;
            break;
    case 5:
            LED4 = ~LED4;
            break;
    case 6:
            LED5 = ~LED5;
            break;
    case 7:
            LED6 = ~LED6;
            break;
    case 8:
            LED7 = ~LED7;
            break;
    case 9:
            LedTest();
            break;
    }

}


