/**
  ******************************************************************************
  * @file    bsp_pvd.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   pvd�������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 �Ե� ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "pvd.h" 



/**
  * @brief  ����PVD.
  * @param  None
  * @retval None
  */
void PVD_Conf(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /*ʹ�� PWR ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); 
      
  /* ���� EXTI16��(PVD ���) �����������½����ж�*/
  EXTI_ClearITPendingBit(EXTI_Line16);
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

	NVIC_EnableIRQ(PVD_IRQn);
	
  /* ����PVD����PWR_PVDLevel_2V6 (PVD����ѹ����ֵΪ2.6V��VDD��ѹ����2.6Vʱ����PVD�ж�) */
	/*���弶������Լ���ʵ��Ӧ��Ҫ������*/
  PWR_PVDLevelConfig(PWR_PVDLevel_2V6);

  /* ʹ��PVD��� */
  PWR_PVDCmd(ENABLE);
}

/*********************************************END OF FILE**********************/
