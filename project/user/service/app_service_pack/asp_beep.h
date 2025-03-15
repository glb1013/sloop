/**
 ******************************************************************************
 * @file    asp_beep
 * @author  ����
 * @date    2025-1-10
 * @brief   ������������֧�ֶ������
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_beep_H
#define __asp_beep_H

#include "sp_common.h"

/* ��ʼ�� */
void asp_beep_init(void);

/* �������� */
void asp_beep(int ms);

/* ������� */
void asp_beep_multiple(int num, int interval, int continues);

#endif /* __asp_beep_H */

/************************** END OF FILE **************************/
