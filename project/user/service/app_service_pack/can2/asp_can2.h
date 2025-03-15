/**
******************************************************************************
* @file    asp_can
* @author  ����
* @date    2025-1-16
* @brief   �ṩ can ���շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#ifndef __asp_can_H
#define __asp_can_H

#include "sp_common.h"

/* can ��ʼ�� */
void asp_can2_init(void);

/* can �������ݻص� */
void asp_can2_receive_callback(CanRxMsg *msg);

/* can �������ݴ��� */
void asp_can2_send(CanTxMsg *msg);

#endif /* __asp_can_H */

/*********************************** END OF FILE ***********************************/
