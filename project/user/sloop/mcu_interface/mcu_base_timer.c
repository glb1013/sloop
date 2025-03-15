/**
 ******************************************************************************
 * @file    mcu_base_timer
 * @author  xuan
 * @date    2024-12-16
 * @brief   �ṩ MCU ������ʱ��
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "mcu_base_timer.h"

void IWDG_init(void);
weak_define(mcu_tick_irq);
void tim100ns_init(void);

/* MCU ������ʱ����ʼ�� */
void mcu_base_timer_init(void)
{
    /* HSE ʱ������ */
    RCC_DeInit();

    SystemInit();

    SystemCoreClockUpdate();

    sys_prt_withFunc("SYSCLK: %d MHz", SystemCoreClock / 1000000);

#if SYS_WDG_ENABLE

    /* ���ÿ��Ź� ��ʱʱ�� 1s */
    IWDG_init();

    sys_printf("watch dog start");

#endif

    /* NVIC����,16����Ӧ���ȼ�����֧����ռ������������ϵͳ���� */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    SysTick_Config(SystemCoreClock / 1000);

    /* ���ȼ���ߣ���֤ tick ʵʱ���� */
    NVIC_SetPriority(SysTick_IRQn, PRIO_HIGHEST);

    tim100ns_init();
}

void SysTick_Handler(void)
{
    mcu_tick_irq();
}

#if SYS_WDG_ENABLE

void IWDG_init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetPrescaler(IWDG_Prescaler_32);

    IWDG_SetReload(1000 - 1);

    IWDG_ReloadCounter();

    IWDG_Enable();
}

/* ι�� */
void mcu_reload_wdg(void)
{
    IWDG_ReloadCounter();
}

#endif

void tim100ns_init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = (6 - 1);
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM7, ENABLE);
}

/* ��ȡ 100ns �ֱ���ʱ��� */
uint16_t mcu_get_100nsRes(void)
{
    return TIM_GetCounter(TIM7);
}

/*********************************** END OF FILE ***********************************/
