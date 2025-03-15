/**
 ******************************************************************************
 * @file    gpio_config
 * @author  ����
 * @date    2025-2-27
 * @brief   GPIO ����
 * ==���ļ��û������� gpio ����==
 *****************************************************************************/

#ifndef __gpio_config_H
#define __gpio_config_H

#include "sp_common.h"

/* gpio �����ַ�����󳤶� */
#define GPIO_STR_MAX 32

typedef struct
{
    /* �ַ��� */
    char str[GPIO_STR_MAX];

    /* ö��ֵ */
    char _enum;

} gpio_map_typ;

enum
{
    L = 0,
    H
};

extern gpio_map_typ gpio_map[];

/* gpio ���� */
void gpio_config(void);

/* �����ŵ�ƽ */
uint8_t gpio_read(char pin);

/* �������ŵ�ƽ������ gpio_write(pin_beep, H); */
void gpio_write(char pin, char bit);

/* �������ŵ�ƽ */
void gpio_H(char pin);

/* �������ŵ�ƽ */
void gpio_L(char pin);

/* ��ת���ŵ�ƽ */
void gpio_toggle(char pin);

/* GPIO ������� */
void gpio_input_echo(void);

/* ============================================================== */

/* GPIO ���÷���
��һ���������涨�� GPIO ����
�ڶ������� gpio_config.c ���� GPIO */

/* ������ GPIO ���� */

enum
{

/* ����sw1 */
#define sw1_port GPIOE
#define sw1_pin GPIO_Pin_0
    pin_sw1,

#define sw2_port GPIOE
#define sw2_pin GPIO_Pin_1
    pin_sw2,

#define sw3_port GPIOE
#define sw3_pin GPIO_Pin_2
    pin_sw3,

#define sw4_port GPIOE
#define sw4_pin GPIO_Pin_3
    pin_sw4,

/* ������ */
#define beep_port GPIOE
#define beep_pin GPIO_Pin_14
    pin_beep,

/* I2C �������� */
#define i2cScl_port GPIOA
#define i2cScl_pin GPIO_Pin_11
    pin_i2cScl,

#define i2cSda_port GPIOA
#define i2cSda_pin GPIO_Pin_12
    pin_i2cSda,

/* ����ָʾ�� */
#define runLed_port GPIOB
#define runLed_pin GPIO_Pin_4
    pin_runLed,

    PIN_NUM,

};

#endif /* __gpio_config_H */

/************************** END OF FILE **************************/
