/**
 ******************************************************************************
 * @file    asp_i2c
 * @author  ����
 * @date    2020-2-20
 * @brief   �ṩGPIOģ��I2C����
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#ifndef __asp_i2c_H
#define __asp_i2c_H

#include "sp_common.h"

#define ADDR_IS_8b 1
#define ADDR_IS_16b 0

/* i2c��ʼ�� */
void asp_i2c_init(void);

/* У��ӽڵ� */
uint8_t asp_i2c_check(uint8_t dev);

/* ���ڵ�д���� */
uint8_t asp_i2c_write_bytes(uint8_t dev, uint16_t addr, uint8_t addr_is_8b,
                            uint8_t *buf, uint16_t len);

/* ���ڵ������ */
uint8_t asp_i2c_read_bytes(uint8_t dev, uint16_t addr, uint8_t addr_is_8b,
                           uint8_t *buf, uint16_t len);

/* ���ڵ�д���ֽ����� */
uint8_t asp_i2c_write_byte(uint8_t dev, uint16_t addr, uint8_t byte);

/* ���ڵ�����ֽ����� */
uint8_t asp_i2c_read_byte(uint8_t dev, uint16_t addr);

#endif /* __asp_i2c_H */

/*********************************** END OF FILE ***********************************/
