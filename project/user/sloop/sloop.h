/**
 ******************************************************************************
 * @file    sloop
 * @author  xuan
 * @date    2024-12-16
 * @brief   �ṩ sloop ϵͳAPI,���糬ʱ/��������Ĵ������������񴴽������������л���
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __sloop_H
#define __sloop_H

#include "bl_common.h"

/* sloop ϵͳ��ʼ�� */
void sloop_init(void);
/* sloop ϵͳ���� */
void sloop(void);

/* ��ȡʱ��� */
uint32_t sys_get_tick(void);
/* ����ʽ��ʱ */
void sys_delay(int ms);

/* ��ȡ us ��ʱ��� */
uint16_t sys_get_us(void);
/* ����ʽ��ʱ */
void sys_delay_us(int us);

/* ��ʱ���� */
void sys_timeout_start(int ms, pfunc task);
void sys_timeout_stop(pfunc task);

/* �������� */
void sys_cycle_start(int ms, pfunc task);
void sys_cycle_stop(pfunc task);

/* ������� */
void sys_multiple_start(int num, int ms, pfunc task);
void sys_multiple_stop(pfunc task);

/* �������� */
void sys_task_start(pfunc task);
void sys_task_stop(pfunc task);

/* ��������ִֻ��һ�Σ����͵� main loop ��ִ�С��������ж��и����߼��·�ִ�� */
void sys_task_once(pfunc task);

/* ���������л� */
void sys_goto(pfunc task);

/* �������ȴ���ʱ���ֻ���ڻ���������ʹ�ã�0���ȴ����, 1���ȴ����ж� */
char sys_wait(int ms);
/* ��������ȴ���ֱ�� break or continue */
char sys_wait_bare(void);

/* �жϵȴ���sys_wait ����1 */
void sys_wait_break(void);
/* ���Եȴ���sys_wait ����0�������ִ�еȴ���Ĳ��� */
void sys_wait_continue(void);
/* ��ȡ�ȴ�״̬ */
char sys_is_waiting(void);

/* ��ӿ���̨���� */
void sys_add_cmd(char *str, pfunc task);
/* ��ȡ����̨�����ַ����������ڻ�ȡ����������Ƽ��� sscanf */
char *sys_get_cmd_str(void);
/* ���ո�������һ���ַ��������ڽ���������� */
char *str_next(char *str);

/* ���ó���汾 */
void sys_set_version(char *str);
/* ��ѯ����汾 */
char *sys_get_version(void);

/* ���� */
void sys_reboot(void);

/* ���ɱ��λ�ã�������뱨�� */
#include "behavior_log.h"

#endif /* __sloop_H */

/************************** END OF FILE **************************/
