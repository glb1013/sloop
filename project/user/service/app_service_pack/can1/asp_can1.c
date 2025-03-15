/**
******************************************************************************
* @file    asp_can
* @author  ����
* @date    2025-1-16
* @brief   �ṩ can ���շ��������������շ����� DMA+FIFO
==���ļ��û���Ӧ���==
*****************************************************************************/

#include "asp_can1.h"
#include "msp_can1.h"
#include "asp_can1_send.h"
#include "asp_can1_receive.h"

/* can ��ʼ�� */
void asp_can1_init(void)
{
    /* can ��ʼ�� */
    msp_can_init();

    /* can ���ͳ�ʼ�� */
    asp_can_send_init();

    /* can ���ճ�ʼ�� */
    asp_can_receive_init();

    sys_prt_withFunc("init: can1");
}

/*********************************** END OF FILE ***********************************/
