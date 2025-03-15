/**
 ******************************************************************************
 * @file    msp_uart
 * @author  ����
 * @date    2025-1-10
 * @brief   �ṩ���ڽ��շ��������������շ�����DMA
 * ==���ļ��û���Ӧ���==
 *****************************************************************************/

#include "msp_uart3.h"

#define MSP_UART3

#include "com_config.h"

#define TX_LEN 128
#define RX_LEN 128
static uint8_t tx_buffer[TX_LEN + 1];
static uint8_t rx_buffer[RX_LEN + 1];

/* ������ճ��ȱ��� */
static uint16_t rxlen;

/* ������ɱ�־ */
static char tx_cplt = 1;

/* ��һ�� DMA ����ֵ */
static int dma_count_old;

static DMA_InitTypeDef DMA_InitStructure;

/* ���ճ�ʱ���� */
static void uart_rx_timeout_process(void);
/* ���ճ�ʱ��� */
static void rx_timeout_checkOut(void);

/* ���ڳ�ʼ�� */
void msp_uart_init(void)
{
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    /* ��������ʱ�� */
    RCC_AHB1PeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);

    USARTx_CLK_CMD(USARTx_CLK, ENABLE);

    DMAX_CLK_CMD(DMAx_CLK, ENABLE);

    /* ============================================================== */

    /* GPIO���� */
    GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);
    GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
    GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
    GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

    /* ============================================================== */

    /* �������� */
    USART_OverSampling8Cmd(USARTx, ENABLE);

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = BAUD_RATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USARTx, &USART_InitStructure);

    /* ============================================================== */

    /* DMA���� */
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USARTx_DR_ADDRESS;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /* ============================================================== */

    /* ����DMA���� */
    DMA_DeInit(USARTx_RX_DMA_STREAM);
    DMA_InitStructure.DMA_Channel = USARTx_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_BufferSize = RX_LEN;
    DMA_Init(USARTx_RX_DMA_STREAM, &DMA_InitStructure);

    USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);

    DMA_Cmd(USARTx_RX_DMA_STREAM, ENABLE);

    /* ============================================================== */

    /* �ж����� */
    NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = PRIO_DEFAULT;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ClearFlag(USARTx, USART_FLAG_TC);

    USART_ITConfig(USARTx, USART_IT_IDLE, ENABLE);
    USART_ITConfig(USARTx, USART_IT_TC, ENABLE);

    /* �������� */
    USART_Cmd(USARTx, ENABLE);
}

/* ���ڿ�ʼ���� */
void msp_uart_start(void)
{
    USART_ClearFlag(USARTx, USART_FLAG_TC);

    USART_ITConfig(USARTx, USART_IT_IDLE, ENABLE);
    USART_ITConfig(USARTx, USART_IT_TC, ENABLE);

    /* �������� */
    USART_Cmd(USARTx, ENABLE);
}

void USARTx_IRQHandler(void)
{
    if (USART_GetITStatus(USARTx, USART_IT_IDLE) == SET)
    {
        dma_count_old = -1;

        /* �������ڳ�ʱ������� */
        sys_task_start(rx_timeout_checkOut);

        /* ���IDLE */
        (void)USARTx->DR;
    }
    else if (USART_GetITStatus(USARTx, USART_IT_TC) == SET)
    {
        tx_cplt = 1;

        msp_uart_txCplt_callback();

        DMA_Cmd(USARTx_TX_DMA_STREAM, DISABLE);

        USART_DMACmd(USARTx, USART_DMAReq_Tx, DISABLE);

        USART_ClearFlag(USARTx, USART_FLAG_TC);
    }
}

/* ���ճ�ʱ��� */
static void rx_timeout_checkOut(void)
{
    int dma_count = DMA_GetCurrDataCounter(USARTx_RX_DMA_STREAM);

    if (dma_count != dma_count_old)
    {
        sys_timeout_start(TIMEOUT_RX, uart_rx_timeout_process);

        if (dma_count == 0)
            sys_error("The serial port received a very long frame, the length > %d", RX_LEN);

        dma_count_old = dma_count;
    }
}

/* ���ճ�ʱ���� */
static void uart_rx_timeout_process(void)
{
    /* ֹͣ���ڳ�ʱ������� */
    sys_task_stop(rx_timeout_checkOut);

    /* �жϽ���DMA */
    DMA_Cmd(USARTx_RX_DMA_STREAM, DISABLE);

    USART_DMACmd(USARTx, USART_DMAReq_Rx, DISABLE);

    rxlen = RX_LEN - DMA_GetCurrDataCounter(USARTx_RX_DMA_STREAM);

#if RX_ECHO

    static int count;

    count++;

    sys_prt_var(count);

    rx_buffer[rxlen] = 0;

    sys_prt_noNewLine(RTT_CTRL_TEXT_BRIGHT_YELLOW "\nuart rx len: %d, data: ", rxlen);

    for (int i = 0; i < rxlen; i++)
        sys_prt_noNewLine(RTT_CTRL_TEXT_BRIGHT_YELLOW "%02x ", rx_buffer[i]);

    sys_prt_noNewLine("\n");

    sys_prt_withFunc(RTT_CTRL_TEXT_BRIGHT_YELLOW "uart rx: %s", rx_buffer);

#endif

    msp_uart_rx_callback(rx_buffer, rxlen);

    /* ������һ�ν��� */
    DMA_DeInit(USARTx_RX_DMA_STREAM);
    DMA_InitStructure.DMA_Channel = USARTx_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_BufferSize = RX_LEN;
    DMA_Init(USARTx_RX_DMA_STREAM, &DMA_InitStructure);

    USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);

    DMA_Cmd(USARTx_RX_DMA_STREAM, ENABLE);
}

/* ���ڷ������ݴ��� */
void msp_uart_tx(uint8_t *data, int len)
{
    /* ��鳤�� */
    if (len > TX_LEN)
    {
        sys_error("uart tx len too long (> %d)", TX_LEN);

        return;
    }

    /* ���TC��־ */
    if (tx_cplt == 0)
    {
        sys_error("The last sending has not been completed yet");

        return;
    }

    /* ��tx_bufferװ������ */
    memcpy(tx_buffer, data, len);

#if TX_ECHO

    static int count;

    count++;

    sys_prt_var(count);

    tx_buffer[len] = 0;

    sys_prt_noNewLine(RTT_CTRL_TEXT_BRIGHT_WHITE "\nuart tx len: %d, data: ", len);

    for (int i = 0; i < len; i++)
        sys_prt_noNewLine(RTT_CTRL_TEXT_BRIGHT_WHITE "%02x ", tx_buffer[i]);

    sys_prt_noNewLine("\n");

    sys_prt_withFunc(RTT_CTRL_TEXT_BRIGHT_WHITE "uart tx: %s", tx_buffer);

#endif

    tx_cplt = 0;

    USART_ClearFlag(USARTx, USART_FLAG_TC);

    DMA_DeInit(USARTx_TX_DMA_STREAM);
    DMA_InitStructure.DMA_Channel = USARTx_TX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)tx_buffer;
    DMA_InitStructure.DMA_BufferSize = len;
    DMA_Init(USARTx_TX_DMA_STREAM, &DMA_InitStructure);

    USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);

    DMA_Cmd(USARTx_TX_DMA_STREAM, ENABLE);
}

/* ���ڽ������ݻص� */
__weak void msp_uart_rx_callback(uint8_t *data, int len)
{
}

/* ������ɻص� */
__weak void msp_uart_txCplt_callback(void)
{
    sys_printf("tx complete");
}

/*********************************** END OF FILE ***********************************/
