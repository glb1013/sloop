/**
******************************************************************************
* @file    asp_can
* @author  暄暄
* @date    2025-1-16
* @brief   提供 can 接收发送驱动及服务，收发都是 DMA+FIFO
==此文件用户不应变更==
*****************************************************************************/

#include "asp_can2.h"
#include "msp_can2.h"
#include "asp_can2_send.h"
#include "asp_can2_receive.h"

/* can 初始化 */
void asp_can2_init(void)
{
    /* can 初始化 */
    msp_can_init();

    /* can 发送初始化 */
    asp_can_send_init();

    /* can 接收初始化 */
    asp_can_receive_init();

    sys_prt_withFunc("init: can2");
}

/*********************************** END OF FILE ***********************************/
