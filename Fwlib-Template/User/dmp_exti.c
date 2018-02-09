#include "dmp_exti.h"



void DMP_EXTI_CONF(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(DMP_EXTI_GPIO_CLK,ENABLE);
												
	/* ���� NVIC �ж�*/
	//NVIC_Configuration();
	
/*--------------------------KEY1����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = DMP_EXTI_GPIO_PIN ;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(DMP_EXTI_GPIO_PORT, &GPIO_InitStructure);
	
	
	
		/* EXTI line mode config */
  GPIO_EXTILineConfig(DMP_EXTI_PORTSOURCE, DMP_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = DMP_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
	NVIC_EnableIRQ(DMP_EXTI_IRQ);
}



/*
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  

  NVIC_InitStructure.NVIC_IRQChannel = DMP_EXTI_IRQ ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

*/


