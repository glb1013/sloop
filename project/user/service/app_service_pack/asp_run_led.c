/**
 ******************************************************************************
 * @file    asp_run_led
 * @author  ����
 * @date    2025-1-10
 * @brief   ����ָʾ��������ÿ����һ�£��������ж��Ƿ�����
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_run_led.h"
#include "gpio_config.h"

/* ָʾ����˸���� */
void run_led_task(void);

/* ��ʼ�� */
void asp_run_led_init(void)
{
    sys_cycle_start(500, run_led_task);

    sys_prt_withFunc("init: run led 1Hz");
}

/* ָʾ����˸���� */
void run_led_task(void)
{
    gpio_toggle(pin_runLed);
}

/************************** END OF FILE **************************/
