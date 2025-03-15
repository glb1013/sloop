/**
******************************************************************************
* @file    asp_uart5
* @author  ����
* @date    2025-1-16
* @brief   �ṩ���ڽ��շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#ifndef __asp_uart5_H
#define __asp_uart5_H

#include "sp_common.h"

/* ���ڳ�ʼ�� */
void asp_uart5_init(void);

/* ���ڽ������ݻص� */
void asp_uart5_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart5_send(uint8_t *data, int len);

#endif /* __asp_uart5_H */

/*********************************** END OF FILE ***********************************/
