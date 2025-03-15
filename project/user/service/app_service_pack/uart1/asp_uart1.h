/**
******************************************************************************
* @file    asp_uart1
* @author  ����
* @date    2025-1-16
* @brief   �ṩ���ڽ��շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#ifndef __asp_uart1_H
#define __asp_uart1_H

#include "sp_common.h"

/* ���ڳ�ʼ�� */
void asp_uart1_init(void);

/* ���ڽ������ݻص� */
void asp_uart1_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart1_send(uint8_t *data, int len);

#endif /* __asp_uart1_H */

/*********************************** END OF FILE ***********************************/
