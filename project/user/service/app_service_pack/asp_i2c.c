/**
 ******************************************************************************
 * @file    asp_i2c
 * @author  ����
 * @date    2020-2-20
 * @brief   �ṩGPIOģ��I2C����
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "asp_i2c.h"
#include "gpio_config.h"

/* д����λ */
#define I2C_W 0
/* ������λ */
#define I2C_R 1

/**** ���ſ��ƺ� ****/
#define I2C_SCL_H() gpio_H(pin_i2cScl)
#define I2C_SCL_L() gpio_L(pin_i2cScl)

#define I2C_SDA_H() gpio_H(pin_i2cSda)
#define I2C_SDA_L() gpio_L(pin_i2cSda)

#define I2C_SDA_READ() gpio_read(pin_i2cSda)

void i2c_delay(void);
void i2c_start(void);
void i2c_stop(void);
void send_byte(uint8_t byte);
uint8_t read_byte(void);
uint8_t wait_ack(void);
void send_ack(void);
void send_nack(void);

/* i2c��ʼ�� */
void asp_i2c_init(void)
{
    /* �ͷ����� */
    i2c_stop();
}

void i2c_delay(void)
{
    /* ����ѭ��������Ƶ����λMHz������ */
    for (int i = 0; i < 120; i++)
        __NOP();
}

/* ���ڵ㷢���I2C�����ź� */
void i2c_start(void)
{
    I2C_SDA_H();
    i2c_delay();

    I2C_SCL_H();
    i2c_delay();

    I2C_SDA_L();
    i2c_delay();
}

/* ���ڵ㷢���I2Cֹͣ�ź� */
void i2c_stop(void)
{
    I2C_SDA_L();
    i2c_delay();

    I2C_SCL_H();
    i2c_delay();

    I2C_SDA_H();
    i2c_delay();
}

/* ����һ���ֽ� */
void send_byte(uint8_t byte)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        I2C_SCL_L();

        if (byte & 0x80)
        {
            I2C_SDA_H();
        }
        else
        {
            I2C_SDA_L();
        }
        i2c_delay();

        I2C_SCL_H();
        i2c_delay();

        byte <<= 1;
    }
}

/* ��ȡһ���ֽ� */
uint8_t read_byte(void)
{
    uint8_t byte = 0;

    I2C_SCL_L();
    I2C_SDA_H();
    i2c_delay();

    for (uint32_t i = 0; i < 8; i++)
    {
        byte <<= 1;

        I2C_SCL_L();
        i2c_delay();

        I2C_SCL_H();
        i2c_delay();

        if (I2C_SDA_READ())
        {
            byte |= 0x01;
        }
    }

    return byte;
}

/* �ȴ��ӽڵ�ack */
uint8_t wait_ack(void)
{
    uint8_t ack = 0;

    I2C_SCL_L();
    I2C_SDA_H();
    i2c_delay();

    I2C_SCL_H();
    i2c_delay();

    ack = I2C_SDA_READ();

    I2C_SCL_L();
    i2c_delay();

    return ack;
}

/* ��ӽڵ㷢��ack */
void send_ack(void)
{
    I2C_SCL_L();

    I2C_SDA_L();
    i2c_delay();

    I2C_SCL_H();
    i2c_delay();

    I2C_SCL_L();
    I2C_SDA_H();
    i2c_delay();
}

/* ��ӽڵ㷢��nack */
void send_nack(void)
{
    I2C_SCL_L();

    I2C_SDA_H();
    i2c_delay();

    I2C_SCL_H();
    i2c_delay();

    I2C_SCL_L();
    I2C_SDA_H();
    i2c_delay();
}

/* У��ӽڵ�
����0��ʾ�豸���� */
uint8_t asp_i2c_check(uint8_t dev)
{
    uint8_t ack = 0;

    /* I2C���� */
    i2c_start();

    /* ���͵�ַ */
    send_byte(dev | I2C_W);

    /* ��ȡack */
    ack = wait_ack();

    /* I2Cֹͣ */
    i2c_stop();

    return ack;
}

/* ���ڵ�д���� */
uint8_t asp_i2c_write_bytes(uint8_t dev, uint16_t addr, uint8_t addr_is_8b,
                            uint8_t *buf, uint16_t len)
{
    uint8_t err = 0;

    /* I2C���� */
    i2c_start();

    /* �����豸��ַ */
    send_byte(dev | I2C_W);

    /* �ȴ�ack */
    if (wait_ack())
    {
        err = 1;
        goto LABEL_END;
    }

    /* ����Ĵ�����8λ��ַ */
    if (addr_is_8b)
    {
        /* ���ͼĴ�����ַ */
        send_byte(addr);
    }
    else
    /* ����Ĵ�����16λ��ַ */
    {
        /* �ȷ���8λ��ַ */
        send_byte(addr >> 8);

        /* �ȴ�ack */
        if (wait_ack())
        {
            err = 1;
            goto LABEL_END;
        }

        /* �ٷ���8λ��ַ */
        send_byte(addr);
    }

    /* �ȴ�ack */
    if (wait_ack())
    {
        err = 1;
        goto LABEL_END;
    }

    /* �������� */
    for (int i = 0; i < len; i++)
    {
        /* ���͵����ֽ� */
        send_byte(*(buf + i));

        /* �ȴ�ack */
        if (wait_ack())
        {
            err = 1;
            goto LABEL_END;
        }
    }

LABEL_END:
    /* I2Cֹͣ */
    i2c_stop();

    return err;
}

/* ���ڵ������ */
uint8_t asp_i2c_read_bytes(uint8_t dev, uint16_t addr, uint8_t addr_is_8b,
                           uint8_t *buf, uint16_t len)
{
    uint8_t err = 0;

    /* I2C���� */
    i2c_start();

    /* �����豸��ַ */
    send_byte(dev | I2C_W);

    /* �ȴ�ack */
    if (wait_ack())
    {
        err = 1;
        goto LABEL_END;
    }

    /* ����Ĵ�����8λ��ַ */
    if (addr_is_8b)
    {
        /* ���ͼĴ�����ַ */
        send_byte(addr);
    }
    else
    /* ����Ĵ�����16λ��ַ */
    {
        /* �ȷ���8λ��ַ */
        send_byte(addr >> 8);

        /* �ȴ�ack */
        if (wait_ack())
        {
            err = 1;
            goto LABEL_END;
        }

        /* �ٷ���8λ��ַ */
        send_byte(addr);
    }

    /* �ȴ�ack */
    if (wait_ack())
    {
        err = 1;
        goto LABEL_END;
    }

    /* I2C���� */
    i2c_start();

    /* �л������ڵ��ȡģʽ */
    send_byte(dev | I2C_R);

    /* �ȴ�ack */
    if (wait_ack())
    {
        err = 1;
        goto LABEL_END;
    }

    /* ��ȡ���� */
    for (int i = 0; i < (len - 1); i++)
    {
        /* ��ȡ�����ֽ� */
        *(buf + i) = read_byte();

        /* ����ack */
        send_ack();
    }

    /* ��ȡ���һ���ֽ� */
    *(buf + len - 1) = read_byte();
    /* ����nack��������ȡ */
    send_nack();

LABEL_END:
    /* I2Cֹͣ */
    i2c_stop();

    return err;
}

/* ���ڵ�д���ֽ����� */
uint8_t asp_i2c_write_byte(uint8_t dev, uint16_t addr, uint8_t byte)
{
    return asp_i2c_write_bytes(dev, addr, ADDR_IS_8b, &byte, 1);
}

/* ���ڵ�����ֽ����� */
uint8_t asp_i2c_read_byte(uint8_t dev, uint16_t addr)
{
    uint8_t byte;

    asp_i2c_read_bytes(dev, addr, ADDR_IS_8b, &byte, 1);

    return byte;
}

/*********************************** END OF FILE ***********************************/
