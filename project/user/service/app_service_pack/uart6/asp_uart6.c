/**
******************************************************************************
* @file    asp_uart6
* @author  暄暄
* @date    2025-1-16
* @brief   提供串口接收发送驱动及服务，收发都是 DMA+FIFO
==此文件用户不应变更==
*****************************************************************************/

#include "asp_uart6.h"
#include "msp_uart6.h"
#include "asp_uart6_send.h"
#include "asp_uart6_receive.h"

/* 串口初始化 */
void asp_uart6_init(void)
{
    /* 串口初始化 */
    msp_uart_init();

    /* 串口发送初始化 */
    asp_uart_send_init();

    /* 串口接收初始化 */
    asp_uart_receive_init();

    sys_prt_withFunc("init: uart6");
}

/*********************************** END OF FILE ***********************************/
