/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο�������*����*****************
**********������GPIOʹ��ģ�弰λ��������λ��������.h�ļ�******************************/

#include "gpio.h"



/***************GPIO��ʼ��ģ��************/
void GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//GPIO_Mode_Out_PP;GPIO_Mode_Out_OD;GPIO_Mode_IPU;GPIO_Mode_IPD;GPIO_Mode_IN_FLOATING;GPIO_Mode_AF_PP;GPIO_Mode_AF_OD;GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/**************************************/




/****************GPIO����ߵ͵�ƽģ��*****
//дһλ��λ
#define GPIOA0_LOW 			(GPIOA->BRR |= GPIO_Pin_0)
#define GPIOA0_HIGH 		(GPIOA->BSRR |= GPIO_Pin_0)
//д����λ
#define GPIOA_WRITE     (GPIOA->ODR)   //GPIOA_WRITE = 0xff
**************************************/

/****************��ȡ��ƽ״̬**************
#define GPIOA0_READ 			(GPIOA->IDR & GPIO_Pin_0)
#define GPIOA_READ 			  (GPIOA->IDR)
**************************************/

