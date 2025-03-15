/**
 ******************************************************************************
 * @file    asp_can_send
 * @author  ����
 * @date    2025-1-15
 * @brief   can ��FIFO�ķ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_can1_send.h"
#include "asp_can1_tx_fifo.h"
#include "msp_can1.h"

/* ����֡���ms */
#define TX_INTERVAL 8

/* ������ɱ�־ */
static uint32_t tx_cplt_tick;

/* FIFO���� */
static void fifo_dequeue(void);
/* can FIFO���� */
static void can_send_dequeue(void);

/* can ���ͳ�ʼ�� */
void asp_can_send_init(void)
{
    asp_fifo_init();

    sys_task_start(fifo_dequeue);
}

/* ��FIFO��can ���� */
void asp_can_send(CanTxMsg *msg)
{
    asp_fifo_enqueue(msg);
}

/* FIFO���� */
static void fifo_dequeue(void)
{
    static char isSending;

    /* ������ */
    if (isSending)
    {
        /* fifo ������ */
        if (asp_fifo_isEmpty())
        {
            /* ���Ϊ����״̬ */
            isSending = 0;
        }

        return;
    }

    /* ���Ϳ��У�����Ƿ������ݿɷ��� */
    if (!asp_fifo_isEmpty())
    {
        /* ���ϴη��ͼ��ʱ�� */
        if ((sys_get_tick() - tx_cplt_tick) > TX_INTERVAL)
        {
            /* ���������� */
            can_send_dequeue();

            /* ���Ϊ���ڷ��� */
            isSending = 1;
        }
    }
}

/* can FIFO���� */
static void can_send_dequeue(void)
{
    static CanTxMsg msg;

    /* ���� */
    asp_fifo_dequeue(&msg);

    /* �������� */
    msp_can_tx(&msg);

    tx_cplt_tick = sys_get_tick();

    if (asp_fifo_isEmpty())
        return;

    sys_timeout_start(TX_INTERVAL, can_send_dequeue);
}

/************************** END OF FILE **************************/
