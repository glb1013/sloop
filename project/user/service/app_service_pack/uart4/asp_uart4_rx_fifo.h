/**
 ******************************************************************************
 * @file    asp_fifo
 * @author  ����
 * @date    2025-1-15
 * @brief   fifo
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_fifo_H
#define __asp_fifo_H

#include "sp_common.h"

/* ��ģ���ں������������� */
#define asp_fifo_init asp_uart4_rx_fifo_init
#define asp_fifo_isEmpty asp_uart4_rx_fifo_isEmpty
#define asp_fifo_isFull asp_uart4_rx_fifo_isFull
#define asp_fifo_enqueue asp_uart4_rx_fifo_enqueue
#define asp_fifo_dequeue asp_uart4_rx_fifo_dequeue
#define asp_fifo_print asp_uart4_rx_fifo_print

/* ÿ֡���ݵ���󳤶� */
#define FRAME_DATA_MAX_SIZE 128

/* ��ʼ�� */
void asp_fifo_init(void);

/* ��� */
char asp_fifo_isEmpty(void);

/* ���� */
char asp_fifo_isFull(void);

/* ��� */
void asp_fifo_enqueue(uint8_t *data, int len);

/* ���� */
void asp_fifo_dequeue(uint8_t *data, int *len);

/* ��ӡFIFO */
void asp_fifo_print(void);

#endif /* __asp_fifo_H */

/************************** END OF FILE **************************/
