/**
 ******************************************************************************
 * @file    asp_uart_send
 * @author  ����
 * @date    2025-1-15
 * @brief   ���ڴ�FIFO�ķ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_uart_send_H
#define __asp_uart_send_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define asp_uart_send_init asp_uart5_send_init
#define asp_uart_send asp_uart5_send

/* ���ڷ��ͳ�ʼ�� */
void asp_uart_send_init(void);

/* ��FIFO�Ĵ��ڷ��� */
void asp_uart_send(uint8_t *data, int len);

#endif /* __asp_uart_send_H */

/************************** END OF FILE **************************/
