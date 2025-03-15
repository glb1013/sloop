/**
******************************************************************************
* @file    asp_uart1
* @author  ����
* @date    2025-1-16
* @brief   �ṩ���ڽ��շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#include "asp_uart1.h"
#include "msp_uart1.h"
#include "asp_uart1_send.h"
#include "asp_uart1_receive.h"

/* ���ڳ�ʼ�� */
void asp_uart1_init(void)
{
    /* ���ڳ�ʼ�� */
    msp_uart_init();

    /* ���ڷ��ͳ�ʼ�� */
    asp_uart_send_init();

    /* ���ڽ��ճ�ʼ�� */
    asp_uart_receive_init();

    sys_prt_withFunc("init: uart1");
}

/*********************************** END OF FILE ***********************************/
