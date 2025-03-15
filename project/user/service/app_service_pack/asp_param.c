/**
 ******************************************************************************
 * @file    asp_param
 * @author  ����
 * @date    2022-2-20
 * @brief   �����ı���ͻ�ԭ,��Ӳ�������ο�ע��ִ��6�����衣
 * Ĭ���� FLASH Ϊ���ʣ���ѡ EEP
 * ==���ļ��û����԰�������Ӳ���==
 *****************************************************************************/

#include "asp_param.h"

/* ����EEP */
#define EEP_RESET 0

/* ���ò����洢���� 0:EEP 1:FLASH */
#define USE_FLASH 1

#if USE_FLASH

#include "msp_flash.h"
#define PARAM_ADDR FLASH_PARAM_BASE
#define msp_param_read(buf, len) msp_flash_read(PARAM_ADDR, buf, len)
#define msp_param_write(buf, len) msp_flash_write(PARAM_ADDR, buf, len)

#else

#include "asp_eep24c64.h"
#define PARAM_ADDR eep24c64_BASE
#define msp_param_read(buf, len) asp_eep24c64_read_bytes(PARAM_ADDR, buf, len)
#define msp_param_write(buf, len) asp_eep24c64_write_bytes(PARAM_ADDR, buf, len)

#endif

/* ============================================================== */
/* ==��1���������ⲿ����== */

/* �ⲿ���� */
extern float convert;

/* �豣��Ĳ��� */
typedef struct
{
    /* ============================================================== */
    /* ==��2����ע��д�����== */

    /* C��CAN�������Ƕ�ϵ�� */
    float convert;

    /* �����ѳ�ʼ����־ */
    char InitFlag[4];

} param_typ;

static param_typ param;

/* �豣��Ĳ���Ĭ��ֵ */
static const param_typ param_Default = {

    /* ============================================================== */
    /* ==��3��������������Ĭ��ֵ== */

    .convert = 1,
    .InitFlag = "SET"};

/* У����� */
void check_param(void);

/* ������ԭ */
void paramRestore(void)
{
    msp_param_read((uint8_t *)&param, sizeof(param));

    /* ============================================================== */
    /* ==��4����ʵ�ֲ�����ԭ== */

    /* ��ԭ���� */
    convert = param.convert;

    sys_prt_float(convert);

    sys_prt_withFunc("parameter restore successful");
}

void param_write(void)
{
    msp_param_write((uint8_t *)&param, sizeof(param));

    sys_prt_withFunc("parameters saved successfully");
}

void asp_param_save(void)
{
    param_typ paramOld;

    /* ��ȡд��ǰ���ݣ������ȶԣ���һ����д�� */
    msp_param_read((uint8_t *)&paramOld, sizeof(paramOld));

    /* ============================================================== */
    /* ==��5����ʵ�ֲ�������== */

    /* ͬ������ */
    param.convert = convert;

    if (!memcmp((void *)&param, (void *)&paramOld, sizeof(param)))
        return;

    /* ������ʱд�� */
    sys_timeout_start(100, param_write);
}

void asp_auto_init_param(void)
{

#if !USE_FLASH

    asp_eep24c64_init();

#endif

/* ����EEP */
#if EEP_RESET

    msp_param_write((uint8_t *)&param_Default, sizeof(param_Default));

    sys_wait(10);

    sys_printf("force write default param");

#endif

    msp_param_read((uint8_t *)&param, sizeof(param));

    /* ��������洢����ʼ4�ֽڲ��� SET ����Ϊ�ǳ�����¼����ִ�в�����ʼ�� */
    if (strcmp(param.InitFlag, param_Default.InitFlag))
    {

#if !USE_FLASH

        /* �Ȳ�����ǰҳ����д�룬��ֹ���������³��� */
        asp_eep24c64_erase_page(PARAM_ADDR);

        sys_wait(10);

#endif

        /* д��Ĭ�ϲ��� */
        msp_param_write((uint8_t *)&param_Default, sizeof(param_Default));

        sys_wait(10);

        sys_printf("init: write default param");
    }

    /* У����� */
    check_param();

    /* ��ԭ���� */
    paramRestore();
}

/* У����� */
void check_param(void)
{
    msp_param_read((uint8_t *)&param, sizeof(param));

    /* ============================================================== */
    /* ==��6����ʵ�ֲ���У��== */

    /* ��ԭ���� */
    convert = param.convert;

    if (!((convert > 0) && (convert < 1000)))
        goto lable;

    return;

lable:

    sys_error("param err, start default param");

#if !USE_FLASH

    /* �Ȳ�����ǰҳ����д�룬��ֹ���������³��� */
    asp_eep24c64_erase_page(PARAM_ADDR);

    sys_wait(10);

#endif

    /* д��Ĭ�ϲ��� */
    msp_param_write((uint8_t *)&param_Default, sizeof(param_Default));

    sys_wait(10);
}

/*********************************** END OF FILE ***********************************/
