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
#define asp_fifo_init asp_can2_rx_fifo_init
#define asp_fifo_isEmpty asp_can2_rx_fifo_isEmpty
#define asp_fifo_isFull asp_can2_rx_fifo_isFull
#define asp_fifo_enqueue asp_can2_rx_fifo_enqueue
#define asp_fifo_dequeue asp_can2_rx_fifo_dequeue
#define asp_fifo_print asp_can2_rx_fifo_print

/* ��ʼ�� */
void asp_fifo_init(void);

/* ��� */
char asp_fifo_isEmpty(void);

/* ���� */
char asp_fifo_isFull(void);

/* ��� */
void asp_fifo_enqueue(CanRxMsg *msg);

/* ���� */
void asp_fifo_dequeue(CanRxMsg *msg);

/* ��ӡFIFO */
void asp_fifo_print(void);

#endif /* __asp_fifo_H */

/************************** END OF FILE **************************/
