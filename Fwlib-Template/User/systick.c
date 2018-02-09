/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο�������*����*****************
**********������������ʱ����*�����ݸ��ֱ�̷��****************************/

#include "systick.h"
#include "core_cm3.h"
#include "misc.h"

static __IO u32 TimingDelay;
 
 
 #if 1
// ��� �̼��⺯�� �� core_cm3.h��
static __INLINE uint32_t SysTick_Init(uint32_t ticks)
{ 
  // reload �Ĵ���Ϊ24bit�����ֵΪ2^24
	if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);
  
  // ���� reload �Ĵ����ĳ�ʼֵ	
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
	
	// �����ж����ȼ�Ϊ 1<<4-1 = 15�����ȼ�Ϊ���
 // NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 
	
	// ���� counter ��������ֵ
  SysTick->VAL   = 0;
	
	// ����systick ��ʱ��Ϊ 72M
	// ʹ���ж�
	// ʹ��systick
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    
  return (0); 
}
#endif

/**
  * @brief  ����ϵͳ�δ�ʱ�� SysTick
  * @param  
         @arg time: ���뵥λ
							#define _ms       1000
              #define _us       1000000
  * @retval ��
  */
void SysTick_Conf(uint32_t time)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0��汾
	if (SysTick_Init(SystemCoreClock / time))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   ���ʼ����ʱ����,10usΪһ����λ
  * @param  
  *		@arg nTime: ��λ��SysTick_Conf����
  * @retval  ��
  */
void Delay(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  ��ȡ���ĳ���
  * @param  ��
  * @retval ��
  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
  */
void Delay_Handler(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}



// couter ��1��ʱ�� ���� 1/systick_clk
// ��counter �� reload ��ֵ��С��0��ʱ��Ϊһ��ѭ��������������ж���ִ���жϷ������
// ͬʱ CTRL �� countflag λ����1
// ��һ��ѭ����ʱ��Ϊ reload * (1/systick_clk)

void SysTick_Delay_Us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	
	for(i=0;i<us;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1	
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Ms( __IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SystemCoreClock/1000);
	
	for(i=0;i<ms;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
		// ����1ʱ����ȡ��λ����0
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

/*******************************************************************************
* �� �� ��         : delay_us
* ��������		   : ��ʱ��������ʱus
* ��    ��         : i
* ��    ��         : ��
*******************************************************************************/
void delay_us(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		 //ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;		   	 //���������
	do
	{
		temp=SysTick->CTRL;		   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}

/*******************************************************************************
* �� �� ��         : delay_ms
* ��������		   : ��ʱ��������ʱms
* ��    ��         : i
* ��    ��         : ��
*******************************************************************************/
void delay_ms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		//ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;			//���������
	do
	{
		temp=SysTick->CTRL;	   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}


void delay(u32 i)
{
	while(i--);
}


/*********************************************END OF FILE**********************/
