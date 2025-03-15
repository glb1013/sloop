/**
 ******************************************************************************
 * @file    bl_config
 * @author  xuan
 * @date    2024-12-18
 * @brief   �ڴ˴����� sloop �����ù���ģ��
 * ==���ļ��û�������==
 *****************************************************************************/

#ifndef __bl_config_H
#define __bl_config_H

/* ��ʱ�������� */
#define TIMEOUT_LIMIT 16

/* ������������ */
#define CYCLE_LIMIT 16

/* ����������� */
#define MULTIPLE_LIMIT 16

/* ������������ */
#define PARALLEL_TASK_LIMIT 32

/* ������������ */
#define ONCE_TASK_LIMIT 16

/* ����̨�������� */
#define SYS_CMD_LIMIT 16

/* ����̨�����ַ����� */
#define SYS_CMD_SIZE 64

/* �������ݴ洢���� */
#define TASK_DATA_LIMIT 64

/* ============================================================== */

/* ���ÿ��Ź� */
#define SYS_WDG_ENABLE 0

/* ����RTT��ӡ */
#define SYS_RTT_ENABLE 1

/* ������Ϊ��־ */
#define BHV_LOG_ENABLE 1

/* ���ÿ���̨ */
#define SYS_CMD_ENABLE 1

#endif /* __bl_config_H */

/************************** END OF FILE **************************/
