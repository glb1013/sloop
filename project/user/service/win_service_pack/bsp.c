#include <windows.h>
#include "stdint.h"
#include "stdio.h"
#include "conio.h"

volatile MMRESULT tickTimer = 0;

volatile LARGE_INTEGER frequency, start, end;

void NVIC_SystemReset(void)
{
}

void gpio_input_echo(void)
{

}


void CALLBACK TimerProc(UINT uTimeId, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    mcu_tick_irq();
}

void mcu_base_timer_init(void)
{
    tickTimer = timeSetEvent(1, 1, TimerProc, (DWORD)NULL, TIME_PERIODIC);

    // 获取时钟频率
    QueryPerformanceFrequency(&frequency);
    // 记录起始时间
    QueryPerformanceCounter(&start);
}

void mcu_reload_wdg(void)
{
}

uint16_t mcu_get_100nsRes(void)
{
    double elapsedTime;
    // 记录结束时间
    QueryPerformanceCounter(&end);

    // 计算执行时间（单位为秒）
    elapsedTime = (double)(end.QuadPart - start.QuadPart) * 10000000 / frequency.QuadPart;
    end = start;
    return (uint16_t)elapsedTime;
}

#define RTT_BUF_SIZE        1024U
#define RTT_BUF_SIZE_MASK   1023U
typedef struct {
    uint16_t flag;
    uint16_t index;
    char buffer[RTT_BUF_SIZE];
} char_dev_buf_t;
volatile char_dev_buf_t rtt_dev_buf = { 0 };

/* 系统控制台 */
void SEGGER_RTT_proc(void)
{
    while (_kbhit()) {
        char val = _getch();
        if (val == '\n' || val == '\r')
        {
            rtt_dev_buf.flag++;
        }
        else
        {
            rtt_dev_buf.buffer[rtt_dev_buf.index++] = val;
            rtt_dev_buf.index &= RTT_BUF_SIZE_MASK;
            rtt_dev_buf.flag = 0;
        }
    }
}

unsigned SEGGER_RTT_HasKey(void)
{
    return (rtt_dev_buf.flag > 0 && rtt_dev_buf.index > 0);
}

unsigned SEGGER_RTT_Read(unsigned BufferIndex, void* pBuffer, unsigned BufferSize)
{
    unsigned NumBytesRead = 0;
    unsigned len;
    if (rtt_dev_buf.index > 0)
    {
        rtt_dev_buf.flag = 0;
        NumBytesRead = rtt_dev_buf.index;
        memcpy(pBuffer, rtt_dev_buf.buffer, NumBytesRead);
        rtt_dev_buf.index = 0;
    }
    return NumBytesRead;
}
