/**
 ******************************************************************************
 * @file    asp_beep
 * @author  ����
 * @date    2025-1-10
 * @brief   ������������֧�ֶ������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_beep.h"
#include "gpio_config.h"

void beep_on(void);
void beep_off(void);
void beep_once(void);

/* ��ʼ�� */
void asp_beep_init(void)
{
    gpio_L(pin_beep);

    sys_prt_withFunc("init: beep");
}

/* �������� */
void asp_beep(int ms)
{
    beep_on();

    sys_timeout_start(ms, beep_off);
}

static int _continues;

/* ������� */
void asp_beep_multiple(int num, int interval, int continues)
{
    /* ���� interval > continues */
    if (interval <= continues)
    {
        sys_error("The interval time should be greater than the continues. interval: %d, continues: %d", interval, continues);

        return;
    }

    _continues = continues;

    sys_multiple_start(num, interval, beep_once);
}

void beep_on(void)
{
    gpio_H(pin_beep);
}

void beep_off(void)
{
    gpio_L(pin_beep);
}

void beep_once(void)
{
    asp_beep(_continues);
}

/************************** END OF FILE **************************/
