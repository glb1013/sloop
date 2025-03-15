/**
 ******************************************************************************
 * @file    msp_uart
 * @author  ����
 * @date    2025-1-10
 * @brief   �ṩ���ڽ��շ��������������շ�����DMA
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __msp_uart_H
#define __msp_uart_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define msp_uart_init msp_uart3_init
#define msp_uart_start msp_uart3_start
#define msp_uart_rx_callback msp_uart3_rx_callback
#define msp_uart_tx msp_uart3_tx
#define msp_uart_txCplt_callback msp_uart3_txCplt_callback
#define uart_rx_timeout_process uart3_rx_timeout_process

/* ���ڳ�ʼ�� */
void msp_uart_init(void);

/* ���ڽ������ݻص� */
void msp_uart_rx_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void msp_uart_tx(uint8_t *data, int len);

/* ������ɻص� */
void msp_uart_txCplt_callback(void);

#endif /* __msp_uart_H */

/*********************************** END OF FILE ***********************************/
