/*************************************************************************************************************
****************main��������**********************************************************************************
***************************************************************************************************************/
#if 0
#include "stm32f10x.h"
#include "include.h"
 
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;        

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	NVIC_Conf();
	// ���ô���
	USART_Conf();
	// ADC ��ʼ��
	ADC_SingleIRQ_Conf();
	
	printf("\r\n ----����һ��ADC��ͨ��DMA��ȡʵ��----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

		delay_ms(100);  
	}
}
/*********************************************END OF FILE**********************/

// ADC ��ͨ���ɼ�

#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	// ���ô���
	USART_Config();
	
	// ADC ��ʼ��
	ADCx_Init();
	
	printf("\r\n ----����һ��ADC��ͨ��DMA��ȡʵ��----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/


// ADC 6ͨ���ɼ�ʵ��

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{		
	// ���ô���
	USART_Config();
	
	// ADC ��ʼ��
	ADCx_Init();
	
	printf("\r\n ----����һ��ADC��ͨ���ɼ�ʵ��----\r\n");
	
	while (1)
	{	
    
			ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
			ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
		
			printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
			printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
			printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
			printf("\r\n CH3 value = %f V \r\n",ADC_ConvertedValueLocal[3]);
			printf("\r\n CH4 value = %f V \r\n",ADC_ConvertedValueLocal[4]);
			printf("\r\n CH5 value = %f V \r\n",ADC_ConvertedValueLocal[5]);
		
			printf("\r\n\r\n");
			Delay(0xffffee);		 
	}
}
/*********************************************END OF FILE**********************/


#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint32_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL*2];        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{		
	uint16_t temp0=0 ,temp1=0;
	// ���ô���
	USART_Config();
	
	// ADC ��ʼ��
	ADCx_Init();
	
	printf("\r\n ----����һ��˫ADC����ͬ���ɼ�ʵ��----\r\n");
	printf("��ӭʹ�ñ���STM32������\n");
	
	while (1)
	{	
    // ȡ��ADC1���ݼĴ����ĸ�16λ�������ADC2��ת������
		temp0 = (ADC_ConvertedValue[0]&0XFFFF0000) >> 16;
		// ȡ��ADC1���ݼĴ����ĵ�16λ�������ADC1��ת������
		temp1 = (ADC_ConvertedValue[0]&0XFFFF);	
		
		ADC_ConvertedValueLocal[0] =(float) temp0/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) temp1/4096*3.3;
		
		printf("\r\n ADCx_1 value = %f V \r\n",
		        ADC_ConvertedValueLocal[1]);
		printf("\r\n ADCx_2 value = %f V \r\n",
		        ADC_ConvertedValueLocal[0]);
		
		printf("\r\n\r\n");
		Delay(0xffffee); 
		 
	}
}
/*********************************************END OF FILE**********************/
#endif

/*************************************************************************************************************
����Ϊmain��������
***************************************************************************************************************/
#include "adc.h"

__IO uint16_t ADC_ConvertedValue;


/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
static void ADC_Single_GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// ���� ADC IO ����ģʽ
	// ����Ϊģ������
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// ��ʼ�� ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);				
}

/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
static void ADC_More_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// ���� ADC IO ����ģʽ
	GPIO_InitStructure.GPIO_Pin = 	ADC_PIN1|
																		ADC_PIN2|
																		ADC_PIN3|
																		ADC_PIN4|
																		ADC_PIN5|
																		ADC_PIN6;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// ��ʼ�� ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);				
}


/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
static void ADC_Double_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// ADCx_1 GPIO ��ʼ��
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_1_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADCx_1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_1_PORT, &GPIO_InitStructure);

	// ADCx_2 GPIO ��ʼ��
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_2_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADCx_2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_2_PORT, &GPIO_InitStructure);	
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADC_SingleIRQ_Mode_Conf(void)
{
	ADC_InitTypeDef ADC_InitStructure;	

	// ��ADCʱ��
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڶ���ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 

	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	// ת��ͨ��1��
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
		
	// ��ʼ��ADC
	ADC_Init(ADCx, &ADC_InitStructure);
	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ���� ADC ͨ��ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL, 1, 
	                         ADC_SampleTime_55Cycles5);
	
	// ADC ת�����������жϣ����жϷ�������ж�ȡת��ֵ
	ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(ADCx, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADC_SingleDMA_Mode_Conf(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// ��DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// ��ADCʱ��
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADCx->DR ) );
	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������СΪ1���������Ĵ�СӦ�õ��ڴ洢���Ĵ�С
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 

	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	// ת��ͨ��1��
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
		
	// ��ʼ��ADC
	ADC_Init(ADCx, &ADC_InitStructure);
	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADCx, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(ADCx, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADC_MoreDMA_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// ��DMAʱ��
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	// ��ADCʱ��
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( u32 ) ( & ( ADC_x->DR ) );
	
	// �洢����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������С��Ӧ�õ�������Ŀ�ĵصĴ�С
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �ڴ����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 

	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;	
		
	// ��ʼ��ADC
	ADC_Init(ADC_x, &ADC_InitStructure);
	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL5, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL6, 6, ADC_SampleTime_55Cycles5);
	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADC_x, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(ADC_x, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC_x));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADC_Double_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// ��DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// ��ADCʱ��
	ADCx_1_APBxClock_FUN ( ADCx_1_CLK, ENABLE );
	ADCx_2_APBxClock_FUN ( ADCx_2_CLK, ENABLE );
	
  /* ------------------DMAģʽ����---------------- */	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&( ADCx_1->DR ));	
	// �洢����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	
	// ��������С��Ӧ�õ�������Ŀ�ĵصĴ�С
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 	
	// �������ݴ�С
	DMA_InitStructure.DMA_PeripheralDataSize = 
	                                  DMA_PeripheralDataSize_Word;	
	// �ڴ����ݴ�С�����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	/* ----------------ADCx_1 ģʽ����--------------------- */
	// ˫ADC�Ĺ���ͬ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;			
	// ��ʼ��ADC
	ADC_Init(ADCx_1, &ADC_InitStructure);	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx_1, ADCx_1_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADCx_1, ENABLE);
	
	
		/* ----------------ADCx_2 ģʽ����--------------------- */
	// ˫ADC�Ĺ���ͬ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = 
	                           ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;			
	// ��ʼ��ADC
	ADC_Init(ADCx_2, &ADC_InitStructure);	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx_2, ADCx_2_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);
	/* ʹ��ADCx_2���ⲿ����ת�� */
  ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	/* ----------------ADCx_1 У׼--------------------- */
	// ����ADC ������ʼת��
	ADC_Cmd(ADCx_1, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx_1);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx_1));	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx_1);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx_1));
	
  /* ----------------ADCx_2 У׼--------------------- */
		// ����ADC ������ʼת��
	ADC_Cmd(ADCx_2, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx_2);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx_2));	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx_2);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx_2));

	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADCx_1, ENABLE);
}


/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADC_SingleIRQ_Conf(void)
{
	ADC_Single_GPIO_Conf();
	ADC_SingleIRQ_Mode_Conf();
	NVIC_EnableIRQ(ADC_IRQ);
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADC_SingleDMA_Conf(void)
{
	ADC_Single_GPIO_Conf();
	ADC_SingleDMA_Mode_Conf();
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADC_MoreDMA_Conf(void)
{
	ADC_More_GPIO_Config();
	ADC_MoreDMA_Mode_Config();
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADC_Double_Conf(void)
{
	ADC_Double_GPIO_Config();
	ADC_Double_Mode_Config();
}

/*********************************************END OF FILE**********************/
