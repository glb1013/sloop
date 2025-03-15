/**
 ******************************************************************************
 * @file    asp_can_send
 * @author  ����
 * @date    2025-1-15
 * @brief   can ��FIFO�ķ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_can_send_H
#define __asp_can_send_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define asp_can_send_init asp_can2_send_init
#define asp_can_send asp_can2_send

/* can ���ͳ�ʼ�� */
void asp_can_send_init(void);

/* ��FIFO�� can ���� */
void asp_can_send(CanTxMsg *msg);

#endif /* __asp_can_send_H */

/************************** END OF FILE **************************/
