/**
 ******************************************************************************
 * @file    main
 * @author  暄暄
 * @date    2024-9-24
 * @brief   主线程，业务逻辑在 tasks 文件夹中
 *****************************************************************************/

#include "common.h"

 /* ============================================================== */
 /* ==用户代码区 开始== */

 /* 第1步：在 main.h 实现任务声明 */

 /* 第2步：在此处实现任务弱定义 */

 /* 基础初始化 */
weak_define(task_baseInit);

/* 空闲 */
weak_define(task_idle);

/* 演示 */
weak_define(task_demo);

/* ==用户代码区 结束== */
/* ============================================================== */

int main(void)
{
    sloop_init();

    /* 跳转到第一个任务 */
    sys_goto(task_baseInit);

    while (1)
    {
        sloop_run();
    }
}

/************************** END OF FILE **************************/
