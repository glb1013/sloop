/**
 ******************************************************************************
 * @file    asp_eep24c64
 * @author  ����
 * @date    2020-2-20
 * @brief   �ṩeep24c64������eep24c64��һ��i2c ��EEPROM��8KB��
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_i2c.h"
#include "asp_eep24c64.h"

/* eep24c64�豸��ַ */
#define DEV 0xA0

#define ADDR_IS_16b 0

static uint32_t tick_start;

/* eep24c64��ʼ�� */
void asp_eep24c64_init(void)
{
    /* i2c��ʼ�� */
    asp_i2c_init();

    if (asp_eep24c64_check() != 0)
    {
        sys_error("eep err");
    }

    /* ����д�� cycle Ҫ�� */
    tick_start = sys_get_tick();

    sys_wait(5);
}

/* У����eep24c64ͨѶ�Ƿ�����������0��ʾ�豸���� */
uint8_t asp_eep24c64_check(void)
{
    return asp_i2c_check(DEV);
}

/* д������ */
void asp_eep24c64_write_bytes(uint16_t addr, uint8_t *buf, uint16_t len)
{
    /* ��鳤�� */
    if (len > 32)
    {
        sys_error("eep write len too long (> 32)");

        return;
    }

    /* ���д�����ڣ�оƬд��������5ms,д��̫Ƶ���׳����� */
    if ((sys_get_tick() - tick_start) <= 5)
    {
        sys_error("eep write cycle < 5ms");

        return;
    }

    /* ���ڵ�д���� */
    if (asp_i2c_write_bytes(DEV, addr, ADDR_IS_16b, buf, len))
    {
        sys_error("eep write err");

        return;
    }

    tick_start = sys_get_tick();
}

/* ��ȡ���� */
void asp_eep24c64_read_bytes(uint16_t addr, uint8_t *buf, uint16_t len)
{
    /* ���д�����ڣ�д������5ms֮����Զ� */
    if ((sys_get_tick() - tick_start) <= 5)
    {
        sys_error("eep read after write < 5ms");

        return;
    }

    /* ���ڵ������ */
    if (asp_i2c_read_bytes(DEV, addr, ADDR_IS_16b, buf, len))
    {
        sys_error("eep read err");

        return;
    }
}

/* ����һҳ */
void asp_eep24c64_erase_page(uint16_t addr)
{
    /* ���д�����ڣ�оƬд��������5ms,д��̫Ƶ���׳����� */
    if ((sys_get_tick() - tick_start) <= 5)
    {
        sys_error("eep write cycle < 5ms");

        return;
    }

    uint8_t buf[32] = {0};

    /* ���ڵ�д���� */
    if (asp_i2c_write_bytes(DEV, addr, ADDR_IS_16b, buf, 32))
    {
        sys_error("eep write err");

        return;
    }

    tick_start = sys_get_tick();
}

/*********************************** END OF FILE ***********************************/
