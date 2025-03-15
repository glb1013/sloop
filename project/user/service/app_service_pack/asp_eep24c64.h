/**
 ******************************************************************************
 * @file    asp_eep24c64
 * @author  ����
 * @date    2020-2-20
 * @brief   �ṩeep24c64������eep24c64��һ��i2c ��EEPROM��8KB��
 *****************************************************************************/

#ifndef __asp_eep24c64_H
#define __asp_eep24c64_H

#include "sp_common.h"

/* ============================================================== */
/* ==�û������� ��ʼ== */

/* ��ʼ��ַ */
#define eep24c64_BASE 0x0000
/* �洢������ */
#define eep24c64_SIZE 0x2000

/* ==�û������� ����== */
/* ============================================================== */

/* eep24c64��ʼ�� */
void asp_eep24c64_init(void);

/* У����eep24c64ͨѶ�Ƿ�����������0��ʾ�豸���� */
uint8_t asp_eep24c64_check(void);

/* д�����ݣ���֧�ֿ�ҳд�룬
��д����������1paga���ڣ�32Bytes�� */
void asp_eep24c64_write_bytes(uint16_t addr, uint8_t *buf, uint16_t len);

/* ��ȡ���� */
void asp_eep24c64_read_bytes(uint16_t addr, uint8_t *buf, uint16_t len);

/* ����һҳ */
void asp_eep24c64_erase_page(uint16_t addr);

#endif /* __asp_eep24c64_H */

/*********************************** END OF FILE ***********************************/
