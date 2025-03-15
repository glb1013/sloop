/**
 ******************************************************************************
 * @file    asp_uart_send
 * @author  ����
 * @date    2025-1-15
 * @brief   ���ڴ�FIFO�ķ�������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_uart2_send.h"
#include "asp_uart2_tx_fifo.h"
#include "msp_uart2.h"

/* ����֡���ms */
#define TX_INTERVAL 8

/* ������ɱ�־ */
static uint32_t tx_cplt_tick;

/* FIFO���� */
static void fifo_dequeue(void);
/* ����FIFO���� */
static void uart_send_dequeue(void);

/* ���ڷ��ͳ�ʼ�� */
void asp_uart_send_init(void)
{
    asp_fifo_init();

    sys_task_start(fifo_dequeue);
}

/* ��FIFO�Ĵ��ڷ��� */
void asp_uart_send(uint8_t *data, int len)
{
    if (len == 0)
    {
        sys_error("Send length is 0");

        return;
    }

    asp_fifo_enqueue(data, len);
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
            uart_send_dequeue();

            /* ���Ϊ���ڷ��� */
            isSending = 1;
        }
    }
}

/* ����FIFO���� */
static void uart_send_dequeue(void)
{
    static int len;
    static uint8_t data[FRAME_DATA_MAX_SIZE];

    /* ���� */
    asp_fifo_dequeue(data, &len);

    /* �������� */
    msp_uart_tx(data, len);
}

/* ������ɻص� */
void msp_uart_txCplt_callback(void)
{
    tx_cplt_tick = sys_get_tick();

    if (asp_fifo_isEmpty())
        return;

    sys_timeout_start(TX_INTERVAL, uart_send_dequeue);
}

/************************** END OF FILE **************************/
