/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο���YFROBOT*****************
**********��������װ7������******************************/

#ifndef __BEEP_H
#define __BEEP_H	 
#include "stm32f10x.h"
#include "gpio.h"



//�������˿ڶ���
#define BEEP PBout(5)	// BEEP,�������ӿ�		   
//���� ������
#define DO  1911
#define RE  1702
#define MI  1516
#define FA  1431
#define SO  1275
#define LA  1136
#define SI  1012

void BEEP_Conf(void);	    //��ʼ��		
void BEEP_ON(u32 times,u16 note); //��������������
#endif


