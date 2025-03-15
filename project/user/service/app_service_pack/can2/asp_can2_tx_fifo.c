/**
 ******************************************************************************
 * @file    asp_fifo
 * @author  ����
 * @date    2025-1-15
 * @brief   fifo
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_can2_tx_fifo.h"

/* FIFO ��������� */
#define FIFO_MAX_SIZE 8

typedef struct
{
    /* �洢֡������ */
    CanTxMsg msg[FIFO_MAX_SIZE];

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
void asp_fifo_enqueue(CanTxMsg *msg)
{
    if (asp_fifo_isFull())
    {
        sys_error("FIFO is full! Cannot enqueue.");

        return;
    }

    /* ���֡������β�� */
    fifo.msg[fifo.tail] = *msg;

    fifo.tail = (fifo.tail + 1) % FIFO_MAX_SIZE;
    fifo.size++;
}

/* ���� */
void asp_fifo_dequeue(CanTxMsg *msg)
{
    if (asp_fifo_isEmpty())
    {
        sys_error("FIFO is empty! Cannot dequeue.");

        return;
    }

    /* �Ӷ���ͷ���Ƴ�֡ */
    *msg = fifo.msg[fifo.head];

    fifo.head = (fifo.head + 1) % FIFO_MAX_SIZE;
    fifo.size--;
}

/* ��ӡFIFO */
void asp_fifo_print(void)
{
    sys_printf("FIFO contents:");

    int index = fifo.head;

    for (int i = 0; i < fifo.size; i++)
    {
        char buff[9] = {0};

        int len = fifo.msg[index].DLC;

        int id = fifo.msg[index].StdId;

        memcpy(buff, fifo.msg[index].Data, len);

        sys_printf("msg %d len: %d, id: %d, data: ", i + 1, len, id);

        for (int i = 0; i < len; i++)
            sys_prt_noNewLine("%02x ", buff[i]);

        sys_prt_noNewLine("\n");

        sys_prt_withFunc("msg: %s", buff);

        index = (index + 1) % FIFO_MAX_SIZE;
    }
}

/************************** END OF FILE **************************/
