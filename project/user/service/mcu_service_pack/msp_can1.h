/**
 ******************************************************************************
 * @file    msp_can
 * @author  ����
 * @date    2024-10-21
 * @brief   can ��������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __msp_can_H
#define __msp_can_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define msp_can_init msp_can1_init
#define msp_can_rx_callback msp_can1_rx_callback
#define msp_can_tx msp_can1_tx
#define can_rx_process can1_rx_process

void msp_can_init(void);

/* ���ջص� */
void msp_can_rx_callback(CanRxMsg *msg);

/* �������� */
void msp_can_tx(CanTxMsg *msg);

#endif /* __msp_can_H */

/************************** END OF FILE **************************/
