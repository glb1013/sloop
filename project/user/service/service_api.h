/**
 ******************************************************************************
 * @file    service_api
 * @author  ����
 * @date    2025-1-27
 * @brief   �������Ӧ�ò��ṩ�� api
 * ==���ļ��û���Ӧ���(���� can id)==
 *****************************************************************************/

#ifndef __service_api_H
#define __service_api_H

#include "sp_common.h"

/* ==������== */

/* ��ʼ�� */
void asp_beep_init(void);

/* �������� */
void asp_beep(int ms);

/* ������� */
void asp_beep_multiple(int num, int interval, int continues);

/* ============================================================== */

/* ==���е�== */

/* ��ʼ�� */
void asp_run_led_init(void);

/* ============================================================== */

/* ==�������籣��== */

/* �Զ���ʼ������ */
void asp_auto_init_param(void);

/* �������� */
void asp_param_save(void);

/* ============================================================== */

/* ==CAN1== */

/* CAN MCB ID */
#define MCB_ID 1
/* CAN FCB ID */
#define FCB_ID 2
/* CAN TCB ID */
#define TCB_ID 3

/* can ��ʼ�� */
void asp_can1_init(void);

/* can �������ݻص� */
void asp_can1_receive_callback(CanRxMsg *msg);

/* can �������ݴ��� */
void asp_can1_send(CanTxMsg *msg);

/* ============================================================== */

/* ==CAN2== */

/* can������ lift */
#define CAN_ENCODER_LIFT 2
/* can������ tube */
#define CAN_ENCODER_TUBE 3
/* can������ carm */
#define CAN_ENCODER_CARM 4

/* can ��ʼ�� */
void asp_can2_init(void);

/* can �������ݻص� */
void asp_can2_receive_callback(CanRxMsg *msg);

/* can �������ݴ��� */
void asp_can2_send(CanTxMsg *msg);

/* ============================================================== */

/* ==����1== */

/* ���ڳ�ʼ�� */
void asp_uart1_init(void);

/* ���ڽ������ݻص� */
void asp_uart1_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart1_send(uint8_t *data, int len);

/* ============================================================== */

/* ==����2== */

/* ���ڳ�ʼ�� */
void asp_uart2_init(void);

/* ���ڽ������ݻص� */
void asp_uart2_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart2_send(uint8_t *data, int len);

/* ============================================================== */

/* ==����3== */

/* ���ڳ�ʼ�� */
void asp_uart3_init(void);

/* ���ڽ������ݻص� */
void asp_uart3_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart3_send(uint8_t *data, int len);

/* ============================================================== */

/* ==����4== */

/* ���ڳ�ʼ�� */
void asp_uart4_init(void);

/* ���ڽ������ݻص� */
void asp_uart4_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart4_send(uint8_t *data, int len);

/* ============================================================== */

/* ==����5== */

/* ���ڳ�ʼ�� */
void asp_uart5_init(void);

/* ���ڽ������ݻص� */
void asp_uart5_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart5_send(uint8_t *data, int len);

/* ============================================================== */

/* ==����6== */

/* ���ڳ�ʼ�� */
void asp_uart6_init(void);

/* ���ڽ������ݻص� */
void asp_uart6_receive_callback(uint8_t *data, int len);

/* ���ڷ������ݴ��� */
void asp_uart6_send(uint8_t *data, int len);

#endif /* __service_api_H */

/************************** END OF FILE **************************/
