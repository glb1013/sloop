/**
 ******************************************************************************
 * @file    asp_can_receive
 * @author  ����
 * @date    2025-1-15
 * @brief   can ��FIFO�Ľ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_can1_receive.h"
#include "asp_can1_rx_fifo.h"
#include "msp_can1.h"

/* FIFO���� */
static void fifo_dequeue(void);

/* can ���ճ�ʼ�� */
void asp_can_receive_init(void)
{
    asp_fifo_init();

    sys_task_start(fifo_dequeue);
}

/* FIFO���� */
static void fifo_dequeue(void)
{
    if (asp_fifo_isEmpty())
        return;

    static CanRxMsg msg;

    /* ���� */
    asp_fifo_dequeue(&msg);

    asp_can_receive_callback(&msg);
}

/* can �������ݴ��� */
void msp_can_rx_callback(CanRxMsg *msg)
{
    asp_fifo_enqueue(msg);
}

/* ��FIFO��can ���ջص� */
__weak void asp_can_receive_callback(CanRxMsg *msg)
{
    char buff[9] = {0};

    int len = msg->DLC;

    int id = msg->StdId;

    memcpy(buff, msg->Data, len);

    sys_printf("can fifo rx, len: %d, id: %d, data: ", len, id);

    for (int i = 0; i < len; i++)
        sys_prt_noNewLine("%02x ", buff[i]);

    sys_prt_noNewLine("\n");

    sys_prt_withFunc("can fifo rx: %s", buff);
}

/************************** END OF FILE **************************/
