/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο���YFROBOT*****************
**********��������װ7������******************************/
#include "beep.h"
#include "sysTick.h"

	    

/******************************************************
Function:   void BEEP_Init(void)
Description:��ʼ��PA8Ϊ�����,��������ʼ��
******************************************************/
void BEEP_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/******************************************************
Function:   void beepBeep(void)
Description:��������������
Input: times ����ʱ��
       note  ����
#define DO  1911
#define RE  1702
#define MI  1516
#define FA  1431
#define SO  1275
#define LA  1136
#define SI  1012
******************************************************/
void BEEP_ON(u32 times,u16 note)
{
	u32 i;
	for(i = times; i>0; i--)
	{
	  BEEP=0;
		SysTick_Delay_Us(note);
		BEEP=1;
    SysTick_Delay_Us(note);
	}	
}


