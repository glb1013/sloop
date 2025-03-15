/**
 ******************************************************************************
 * @file    mcu_base_timer
 * @author  xuan
 * @date    2024-12-16
 * @brief   �ṩ MCU ������ʱ��
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __mcu_base_timer_H
#define __mcu_base_timer_H

#include "bl_common.h"

/* MCU ������ʱ����ʼ�� */
void mcu_base_timer_init(void);

/* MCU tick �ж� */
void mcu_tick_irq(void);

/* ι�� */
void mcu_reload_wdg(void);

/* ��ȡ 100ns �ֱ���ʱ��� */
uint16_t mcu_get_100nsRes(void);

#endif /* __mcu_base_timer_H */

/*********************************** END OF FILE ***********************************/
