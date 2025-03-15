/**
 ******************************************************************************
 * @file    behavior_log
 * @author  xuan
 * @date    2024-12-18
 * @brief   �� bl_config.h �п�����Ϊ��־���ܡ�
 * ������Ϊ��־�󣬻��ϵͳ API ���д�ӡ��ǿ�����ڵ���ϵͳ API ʱ������Ӧ��־�����
 * ��Է���ϵͳ�������̻��а�����
 *
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __behavior_log_H
#define __behavior_log_H

#include "bl_config.h"

#if !SYS_RTT_ENABLE

#undef BHV_LOG_ENABLE

#define BHV_LOG_ENABLE 0

#endif

/* ����������ע��� */
void add_task_name(pfunc task, char *str);

#if BHV_LOG_ENABLE

#define sys_delay(ms)                         \
    do                                        \
    {                                         \
        sys_prt_withFunc("delay: %d ms", ms); \
        sys_delay(ms);                        \
    } while (0)

/* ============================================================== */

#define sys_timeout_start(ms, task)                                   \
    do                                                                \
    {                                                                 \
        sys_prt_withFunc("timeout task start: %d ms, %s", ms, #task); \
        sys_timeout_start(ms, task);                                  \
    } while (0)

#define sys_timeout_stop(task)                             \
    do                                                     \
    {                                                      \
        sys_prt_withFunc("timeout task stop:  %s", #task); \
        sys_timeout_stop(task);                            \
    } while (0)

/* ============================================================== */

#define sys_cycle_start(ms, task)                                   \
    do                                                              \
    {                                                               \
        add_task_name(task, #task);                                 \
        sys_prt_withFunc("cycle task start: %d ms, %s", ms, #task); \
        sys_cycle_start(ms, task);                                  \
    } while (0)

#define sys_cycle_stop(task)                             \
    do                                                   \
    {                                                    \
        sys_prt_withFunc("cycle task stop:  %s", #task); \
        sys_cycle_stop(task);                            \
    } while (0)

/* ============================================================== */

#define sys_task_start(task)                                \
    do                                                      \
    {                                                       \
        add_task_name(task, #task);                         \
        sys_prt_withFunc("parallel task start: %s", #task); \
        sys_task_start(task);                               \
    } while (0)

#define sys_task_stop(task)                                 \
    do                                                      \
    {                                                       \
        sys_prt_withFunc("parallel task stop:  %s", #task); \
        sys_task_stop(task);                                \
    } while (0)

/* ============================================================== */

#define sys_goto(task)                      \
    do                                      \
    {                                       \
        add_task_name(task, #task);         \
        sys_prt_withFunc("goto %s", #task); \
        sys_goto(task);                     \
    } while (0)

#endif /* BHV_LOG_ENABLE */

#endif /* __behavior_log_H */

/************************** END OF FILE **************************/
