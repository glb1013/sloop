/**
 ******************************************************************************
 * @file    task_baseInit
 * @author  ����
 * @date    2025-1-13
 * @brief   ������ʼ��
 *****************************************************************************/

#include "common.h"

/* ����������ʼ�� */
void task_baseInit(void)
{
    _INIT; /* ���ν�������ʱ��ִ��һ�� */

    /* ���ó���汾 */
    sys_set_version("sloop Demo V1.0.0");

    /* gpio ���� */
    gpio_config();

    /* ���еƳ�ʼ�� */
    asp_run_led_init();

    /* ��������ʼ�� */
    asp_beep_init();

    /* can1 ��ʼ�� */
    asp_can1_init();

    /* can2 ��ʼ�� */
    asp_can2_init();

    /* ����1 ��ʼ�� */
    asp_uart1_init();

    /* ����2 ��ʼ�� */
    asp_uart2_init();

    /* ����3 ��ʼ�� */
    asp_uart3_init();

    /* ����4 ��ʼ�� */
    asp_uart4_init();

    /* ����5 ��ʼ�� */
    asp_uart5_init();

    /* ����6 ��ʼ�� */
    asp_uart6_init();

    asp_beep(100);

    sys_wait(100);

    sys_goto(task_idle);

    _FREE; /* �������������ִ��ʱ���ͷ���Դ */

    _RUN; /* �·���ʼ�������������߼� */
}

/************************** END OF FILE **************************/
