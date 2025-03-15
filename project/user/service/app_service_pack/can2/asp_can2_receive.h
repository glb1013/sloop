/**
 ******************************************************************************
 * @file    asp_can_receive
 * @author  ����
 * @date    2025-1-15
 * @brief   can ��FIFO�Ľ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_can_receive_H
#define __asp_can_receive_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define asp_can_receive_init asp_can2_receive_init
#define asp_can_receive_callback asp_can2_receive_callback

/* can ���ճ�ʼ�� */
void asp_can_receive_init(void);

/* ��FIFO�� can ���ջص� */
void asp_can_receive_callback(CanRxMsg *msg);

#endif /* __asp_can_receive_H */

/************************** END OF FILE **************************/
