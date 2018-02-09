 #if 0
 static void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */ 
int main(void)
{	
		NVIC_Conf();
	// ����LED GPIO�����ر�LED
	LED_GPIO_Config();	

	Delay(0X8FFFFF);
	/*------------------------------------------------------------*/
		/* ����Ƿ�Ϊ�������Ź���λ */
  if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
  {
    /* �������Ź���λ */
    /*  ����� */
    LED_RED;

    /* �����־ */
    RCC_ClearFlag();
		
		/*���һֱ��ι������һֱ��λ������ǰ�����ʱ���ῴ�������˸
		��1s ʱ����ι���Ļ������������̵�*/
  }
  else
  {
    /*���Ƕ������Ź���λ(����Ϊ�ϵ縴λ�����ֶ�������λ֮���) */
    /* ������ */
    LED_BLUE;
  }
	/*--------------------------------------------------------------*/
	
	// ���ð���GPIO
	Key_GPIO_Config();
	// IWDG 1s ��ʱ���
	IWDG_Config(IWDG_Prescaler_64 ,625);
	
	//while��������������Ŀ�о�����Ҫд�Ĵ��룬�ⲿ�ֵĳ�������ö������Ź������
    //�������֪���ⲿ�ִ����ִ��ʱ�䣬������500ms����ô���ǿ������ö������Ź���
	//���ʱ����600ms����500ms��һ�㣬���Ҫ����صĳ���û���ܷ�����ִ�еĻ�����ô
	//ִ�����֮��ͻ�ִ��ι���ĳ�����������ܷ����ǳ���ͻᳬʱ�����ﲻ��ι��
	//�ĳ���,��ʱ�ͻ����ϵͳ��λ������Ҳ���ų������ܷ������ܻ����ˣ��պ�ι���ˣ�
	//������š�����Ҫ�����ȷ�ļ�س��򣬿���ʹ�ô��ڿ��Ź������ڿ��Ź��涨������
	//�涨�Ĵ���ʱ����ι����
	while(1)                        
	{	
// ���������Ҫ����صĴ��룬����о�ȥ������ģ��ι�����Ѱ���ɨ�����ȥ��
//--------------------------------------------------------------------------
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
		{
			// ι���������ι����ϵͳ��Ḵλ��LED1�����һ�Σ������1s
			// ʱ����׼ʱι���Ļ������᳣̻��
			IWDG_Feed();
			//ι�������̵�
			LED_GREEN;
		}   
	}
//---------------------------------------------------------------------------
}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}


/*********************************************END OF FILE**********************/
 #endif
 
 #include "iwdg.h"   

/*
 * ���� IWDG �ĳ�ʱʱ��
 * Tout = prv/40 * rlv (s)
 *      prv������[4,8,16,32,64,128,256]
 * prv:Ԥ��Ƶ��ֵ��ȡֵ���£�
 *     @arg IWDG_Prescaler_4: IWDG prescaler set to 4
 *     @arg IWDG_Prescaler_8: IWDG prescaler set to 8
 *     @arg IWDG_Prescaler_16: IWDG prescaler set to 16
 *     @arg IWDG_Prescaler_32: IWDG prescaler set to 32
 *     @arg IWDG_Prescaler_64: IWDG prescaler set to 64
 *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
 *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
 *
 * rlv:Ԥ��Ƶ��ֵ��ȡֵ��ΧΪ��0-0XFFF
 * �������þ�����
 * IWDG_Config(IWDG_Prescaler_64 ,625);  // IWDG 1s ��ʱ���
 */

void IWDG_Conf(uint8_t prv ,uint16_t rlv)
{	
	// ʹ�� Ԥ��Ƶ�Ĵ���PR����װ�ؼĴ���RLR��д
	IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
	
	// ����Ԥ��Ƶ��ֵ
	IWDG_SetPrescaler( prv );
	
	// ������װ�ؼĴ���ֵ
	IWDG_SetReload( rlv );
	
	// ����װ�ؼĴ�����ֵ�ŵ���������
	IWDG_ReloadCounter();
	
	// ʹ�� IWDG
	IWDG_Enable();	
}

// ι��
void IWDG_Feed(void)
{
	// ����װ�ؼĴ�����ֵ�ŵ��������У�ι������ֹIWDG��λ
	// ����������ֵ����0��ʱ������ϵͳ��λ
	IWDG_ReloadCounter();
}


/*********************************************END OF FILE**********************/
