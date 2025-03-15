/**
 ******************************************************************************
 * @file    asp_uart_receive
 * @author  ����
 * @date    2025-1-15
 * @brief   ���ڴ�FIFO�Ľ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_uart_receive_H
#define __asp_uart_receive_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define asp_uart_receive_init asp_uart5_receive_init
#define asp_uart_receive_callback asp_uart5_receive_callback

/* ���ڽ��ճ�ʼ�� */
void asp_uart_receive_init(void);

/* ��FIFO�Ĵ��ڽ��ջص� */
void asp_uart_receive_callback(uint8_t *data, int len);

#endif /* __asp_uart_receive_H */

/************************** END OF FILE **************************/
