 #if 0
 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */ 
int main(void)
{	
	uint8_t wwdg_tr, wwdg_wr; 
	
	NVIC_Conf();
	
	// ����LED GPIO�����ر�LED
	LED_GPIO_Config();

	LED1(ON) ;
	SOFT_Delay(0X00FFFFFF);	
	
	// ��ʼ��WWDG�����ü�������ʼֵ�������ϴ���ֵ������WWDG��ʹ����ǰ�����ж�
	WWDG_Config(0X7F, 0X5F, WWDG_Prescaler_8);
	
	// ����ֵ�����ڳ�ʼ����ʱ�����ó�0X5F�����ֵ����ı�
	wwdg_wr = WWDG->CFR & 0X7F;

	while(1)
	{	
		LED1(OFF);
		//-----------------------------------------------------
		// �ⲿ��Ӧ��д��Ҫ��WWDG��صĳ�����γ������е�ʱ��
		// �����˴���ֵӦ�����óɶ��
		//-----------------------------------------------------
		
		// ��ʱ��ֵ����ʼ�������0X7F��������WWDGʱ�����ֵ�᲻�ϼ�С
		// ����������ֵ���ڴ���ֵʱι���Ļ����Ḵλ�������������ٵ�0X40
		// ��û��ι���Ļ��ͷǳ��ǳ�Σ���ˣ��������ټ�һ�ε���0X3Fʱ�͸�λ
		// ����Ҫ����������ֵ�ڴ���ֵ��0X40֮���ʱ��ι��������0X40�ǹ̶��ġ�
		wwdg_tr = WWDG->CR & 0X7F;
		
		if( wwdg_tr < wwdg_wr )
		{
			// ι�����������ü�������ֵΪ���0X7F
			// 
			WWDG_Feed();
		}
	}
}
 #endif



#include "wwdg.h"   



/* WWDG ���ú���
 * tr ���ݼ���ʱ����ֵ�� ȡֵ��ΧΪ��0x7f~0x40
 * wr ������ֵ��ȡֵ��ΧΪ��0x7f~0x40
 * prv��Ԥ��Ƶ��ֵ��ȡֵ������
 *      @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1(36MHZ)/4096)/1
 *      @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1(36mhz)/4096)/2
 *      @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1(36mhz)/4096)/4
 *      @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1(36mhz)/4096)/8
 */
void WWDG_Conf(uint8_t tr, uint8_t wr, uint32_t prv)
{	
	// ���� WWDG ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// ���õݼ���������ֵ
	WWDG_SetCounter( tr );
	
	// ����Ԥ��Ƶ����ֵ
	WWDG_SetPrescaler( prv );
	
	// �����ϴ���ֵ
	WWDG_SetWindowValue( wr );
	
	// ���ü�������ֵ��ʹ��WWDG
	WWDG_Enable(WWDG_CNT);	
	
	// �����ǰ�����жϱ�־λ
	WWDG_ClearFlag();	
	// ʹ��WWDG�ж�
	NVIC_EnableIRQ(WWDG_IRQn);
	// ��WWDG �ж�
	WWDG_EnableIT();
}

// ι��
void WWDG_Feed(void)
{
	// ι����ˢ�µݼ���������ֵ�����ó����WDG_CNT=0X7F
	WWDG_SetCounter( WWDG_CNT );
}


/*********************************************END OF FILE**********************/
