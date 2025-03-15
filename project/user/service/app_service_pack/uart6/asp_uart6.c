/**
******************************************************************************
* @file    asp_uart6
* @author  ����
* @date    2025-1-16
* @brief   �ṩ���ڽ��շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#include "asp_uart6.h"
#include "msp_uart6.h"
#include "asp_uart6_send.h"
#include "asp_uart6_receive.h"

/* ���ڳ�ʼ�� */
void asp_uart6_init(void)
{
    /* ���ڳ�ʼ�� */
    msp_uart_init();

    /* ���ڷ��ͳ�ʼ�� */
    asp_uart_send_init();

    /* ���ڽ��ճ�ʼ�� */
    asp_uart_receive_init();

    sys_prt_withFunc("init: uart6");
}

/*********************************** END OF FILE ***********************************/
