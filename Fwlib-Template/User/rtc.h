#ifndef _rtc_H
#define _rtc_H
#include "stm32f10x.h"

//����ȫ�ֱ���
extern u8 timebz;
extern u8 timeclock;
extern uint8_t Lunar1[200],Lunar2[200],Term24[200];
void RTC_Conf(void);
void RTC_CLOCK_Conf(void);
void Time_Calculate(uint32_t TimeVar);

//����ʱ���ʱ��������
#define TIME_ZOOM						(8*60*60)

#endif
