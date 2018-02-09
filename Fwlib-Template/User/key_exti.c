/*********188������ר��key����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
**********�����������жϳ�ʼ���ֿ���������������������Ӳ������*****************************/

#include "key_exti.h"

/*
����Ƕ�������жϿ�����NVIC����̬���������ܱ��ⲿ����
*/

/*
static void NVIC_Conf(void)
{
	//����NVIC��ʼ���ṹ�壬ѡ���ȼ���1,�����ýṹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   //�����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ʹ���ж�
	//����KEYUP��NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEYUP_INT_EXTI_IRQ;  //ѡ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
	//����KEY0��NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_INT_EXTI_IRQ;  //ѡ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
	//����KEY1��NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;  //ѡ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
	//����KEY2��NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;  //ѡ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
}
*/

void KEYUP_EXTI_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEYUP_INT_GPIO_CLK,ENABLE);
	//NVIC_Conf();  //����NVIC
	
	 GPIO_InitStructure.GPIO_Pin = KEYUP_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(KEYUP_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEYUP_INT_EXTI_PORTSOURCE, KEYUP_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEYUP_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_EnableIRQ(KEYUP_INT_EXTI_IRQ);
}

void KEY0_EXTI_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEY0_INT_GPIO_CLK,ENABLE);
	//NVIC_Conf();   //����NVIC
	
	 GPIO_InitStructure.GPIO_Pin = KEY0_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY0_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY0_INT_EXTI_PORTSOURCE, KEY0_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY0_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	 NVIC_EnableIRQ(KEY0_INT_EXTI_IRQ);
}

void KEY1_EXTI_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEY0_INT_GPIO_CLK,ENABLE);
	//NVIC_Conf();      //����NVIC
	
	 GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_EnableIRQ(KEY1_INT_EXTI_IRQ);
}

void KEY2_EXTI_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);
	//NVIC_Conf();   //����NVIC
	
	 GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY0_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_EnableIRQ(KEY2_INT_EXTI_IRQ);
}

