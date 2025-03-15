/**
 ******************************************************************************
 * @file    asp_fifo
 * @author  ����
 * @date    2025-1-15
 * @brief   fifo
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_uart4_rx_fifo.h"

/* FIFO ��������� */
#define FIFO_MAX_SIZE 8

typedef struct
{
    /* ֡���� */
    int len;

    uint8_t data[FRAME_DATA_MAX_SIZE + 1];

} Frame;

typedef struct
{
    /* �洢֡������ */
    Frame buffer[FIFO_MAX_SIZE];

    /* ָ�����ͷ�� */
    int head;

    /* ָ�����β�� */
    int tail;

    /* ��ǰ�����е�Ԫ������ */
    int size;

} FIFO;

static FIFO fifo;

void asp_fifo_init(void)
{
    fifo.head = 0;
    fifo.tail = 0;
    fifo.size = 0;
}

/* ��� */
char asp_fifo_isEmpty(void)
{
    return fifo.size == 0;
}

/* ���� */
char asp_fifo_isFull(void)
{
    return fifo.size == FIFO_MAX_SIZE;
}

/* ��� */
void asp_fifo_enqueue(uint8_t *data, int len)
{
    if (asp_fifo_isFull())
    {
        sys_error("FIFO is full! Cannot enqueue.");

        return;
    }
    
    if (len > FRAME_DATA_MAX_SIZE)
    {
        sys_error("Frame data len too long (> %d)", FRAME_DATA_MAX_SIZE);

        return;
    }

    /* ���֡������β�� */
    fifo.buffer[fifo.tail].len = len;
    memcpy(fifo.buffer[fifo.tail].data, data, len);

    fifo.tail = (fifo.tail + 1) % FIFO_MAX_SIZE;
    fifo.size++;
}

/* ���� */
void asp_fifo_dequeue(uint8_t *data, int *len)
{
    if (asp_fifo_isEmpty())
    {
        sys_error("FIFO is empty! Cannot dequeue.");

        return;
    }

    /* �Ӷ���ͷ���Ƴ�֡ */
    *len = fifo.buffer[fifo.head].len;
    memcpy(data, fifo.buffer[fifo.head].data, *len);

    fifo.head = (fifo.head + 1) % FIFO_MAX_SIZE;
    fifo.size--;
}

/* ��ӡFIFO */
void asp_fifo_print(void)
{
    sys_printf("FIFO contents:");

    int len = 0;

    int index = fifo.head;

    for (int i = 0; i < fifo.size; i++)
    {
        len = fifo.buffer[index].len;

        sys_printf("Frame %d: len = %d, Data = ", i + 1, len);

        fifo.buffer[index].data[len] = 0;

        sys_printf("%s", fifo.buffer[index].data);

        index = (index + 1) % FIFO_MAX_SIZE;
    }
}

/************************** END OF FILE **************************/
