/**
******************************************************************************
* @file    asp_uart2
* @author  ����
* @date    2025-1-16
* @brief   �ṩ���ڽ��շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#include "asp_uart2.h"
#include "msp_uart2.h"
#include "asp_uart2_send.h"
#include "asp_uart2_receive.h"

/* ���ڳ�ʼ�� */
void asp_uart2_init(void)
{
    /* ���ڳ�ʼ�� */
    msp_uart_init();

    /* ���ڷ��ͳ�ʼ�� */
    asp_uart_send_init();

    /* ���ڽ��ճ�ʼ�� */
    asp_uart_receive_init();

    sys_prt_withFunc("init: uart2");
}

/*********************************** END OF FILE ***********************************/
