/**
 ******************************************************************************
 * @file    msp_flash
 * @author  ����
 * @date    2024-10-21
 * @brief   mcu flash ����������֧�Ų����ѻ�����
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __msp_flash_H
#define __msp_flash_H

#include "sp_common.h"

/* ������ʼλ�� 384k */
#define FLASH_PARAM_BASE (FLASH_BASE + 0x60000)

/* ������ */
void msp_flash_read(uint32_t addr, uint8_t *buf, uint32_t len);

/* д���� */
void msp_flash_write(uint32_t addr, uint8_t *buf, uint32_t len);

#endif /* __msp_flash_H */

/************************** END OF FILE **************************/
