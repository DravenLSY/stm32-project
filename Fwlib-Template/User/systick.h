/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο�������*����*****************
**********������������ʱ����*�����ݸ��ֱ�̷��****************************/

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
#define _ms       1000
#define _us       1000000


//���ݸ��ֱ�̷��
#define delay_ms     					Delay_Ms
#define delay_us     					Delay_Us
#define SYSTICK_Delay1ms      delay_ms
#define DELAY_MS              Delay_Ms
#define DELAY_US     					Delay_Us
#define Delay_us              Delay_Us
#define Delay_ms              Delay_Ms

//���ʼ�����жϷ�����
void SysTick_Conf(uint32_t time);
void Delay(__IO u32 nTime);

//�����ʼ�����жϷ�����
void SysTick_Delay_Us( __IO uint32_t us);
void SysTick_Delay_Ms( __IO uint32_t ms);

//ֱ�Ӳ����Ĵ���
void Delay_Us(u32 i);
void Delay_Ms(u32 i);

//������������
void delay(u32 i);

#endif /* __SYSTICK_H */
