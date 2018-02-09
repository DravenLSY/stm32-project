//ʹ������
/*********************************************************************************************************************************************
 *#include "stm32f10x.h"
 *#include "include.h"

  //   ע��ʹ��ʱ�ȵ��ó�ʼ��������ʼ��IO���ã�Ȼ��ѡ����,ѡ��Ƶ��ֵ�����Ⱥ�˳�򣩼��������
	//   ����ad9834��ͨ��дad9834��16λ���ƼĴ�����ʵ����������
	//   �ó���Ĭ��ʹ��FREQ0��PHASE0��δ����λ��������

	//IOUT��IOUTB���������������ѹ��������Ҳ������ǲ�
	//SIGN BIT OUT����������÷����������ź���оƬ�ڲ��˲�������Ƚ����õ�������Ƚ��������Ҳ�Ƶ���費С��3MHz��������ֵΪ0-DVDD
	//AVDD��DVDD��Χ��2.3-5.5V
	//���Ƶ��ӦС�ڲο�Ƶ�ʵ�33%
	//Ϊ��֤�ﵽ����ܣ������ѹӦС��VDD-1.5V�����˳�ӵ�ѹ��

	int main()
	{	
		//��ʼ��ad9834���ĸ�IO
		Init_AD9834();
		
		//��λad9834�ڲ��Ĵ������ص��������ѡ����
		//���ǲ�Triangle_Wave�����Ҳ�(��������)Sine_Wave�����Ҳ�(������)Sine_Cube_Wave
		AD9834_Reset(Sine_Cube_Wave);
		
		//����Ƶ��4MHz���궨��Ĳ�������16λĬ��ʹ�õ�FREQ0
		AD9834_Set_Freq(FREQ_0,4000000);
		
		//��ʼ�������
		AD9834_Select_Wave(Sine_Cube_Wave);
		
		//��ѭ��
		while(1);
	}
***********************************************************************************************************************************************/

#include "stm32f10x.h"
#include "ad9834.h"

/****************************************************************
��������: AD9834_Write_16Bits
��    ��: ��AD9834д��16Ϊ����
��    ��: data --  Ҫд���16λ���� MSB
����ֵ  : ��
*****************************************************************/
/*
ʱ��FSYNC��0��һ֡��ʼ����1��һ֡����
			SCLK��0���������ݣ���1���ı�����
			MSB��λ���У�һ֡16λ
*/
void AD9834_Write_16Bits(unsigned int data)
{
    unsigned char i = 0 ;
	
    AD9834_SCLK_CLR;
    AD9834_SCLK_SET ;
    AD9834_FSYNC_CLR ;
    for(i=0 ;i<16 ;i++) 
    {
        if(data & 0x8000)
          AD9834_SDATA_SET ;
        else
          AD9834_SDATA_CLR ;
        
        AD9834_SCLK_CLR ;
        data <<= 1 ;
				delay_us(5);
        AD9834_SCLK_SET ;
    }
    
    AD9834_FSYNC_SET ;
}



/***********************************************************************************
�������ƣ�AD9834_Select_Wave
��    �ܣ����Ϊ���ƣ�
    --------------------------------------------------
    IOUT���Ҳ� ��SIGNBITOUT���� ��дFREQREG0 ��дPHASE0
    ad9834_write_16bit(0x2028)   һ����дFREQREG0
    ad9834_write_16bit(0x0038)   ������дFREQREG0��LSB
    ad9834_write_16bit(0x1038)   ������дFREQREG0��MSB
    --------------------------------------------------
    IOUT���ǲ� ��дPHASE0
    ad9834_write_16bit(0x2002)   һ����дFREQREG0
    ad9834_write_16bit(0x0002)   ������дFREQREG0��LSB
    ad9834_write_16bit(0x1008)   ������дFREQREG0��MSB
��    ����initdata -- Ҫ���������
����ֵ  ����
************************************************************************************/
void AD9834_Select_Wave(unsigned int initdata)
{
    AD9834_FSYNC_SET;
    AD9834_SCLK_SET;
    
//    AD9834_RESET_SET;
//    AD9834_RESET_SET;
//    AD9834_RESET_CLR;
     
    AD9834_Write_16Bits(initdata);
}


//��λad9834�ڲ��Ĵ���
void AD9834_Reset(unsigned int initdata)
{
    AD9834_FSYNC_SET;
    AD9834_SCLK_SET;
    
//    AD9834_RESET_SET;
//    AD9834_RESET_SET;
//    AD9834_RESET_CLR;
     
    AD9834_Write_16Bits(initdata|0x0100);
}

/****************************************************************
��������: Init_AD9834
��    ��: ��ʼ��AD9834��������
��    ��: ��
����ֵ  : ��
*****************************************************************/
void Init_AD9834(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin = AD9834_FSYNC | AD9834_SCLK | AD9834_SDATA  ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_Init(AD9834_Control_Port ,&GPIO_InitStructure) ;
}


/****************************************************************
��������: AD9834_Set_Freq
��    ��: ����Ƶ��ֵ
��    ��: freq_number -- Ҫд���ƽ�ʼĴ���(FREQ_0��FREQ_1)
          freq -- Ƶ��ֵ (Freq_value(value)=Freq_data(data)*FCLK/2^28)
����ֵ  : ��
*****************************************************************/
/*
Ƶ�ʼĴ���������14λ�Ĵ������
ͨ����16λ��������������д������дƵ�ʼĴ������ȵ�14λ�����14λ
DB15=0��DB14=1ʱ��DB0-DB13ΪFREQ0��14λ
DB15=1��DB14=0ʱ��DB0-DB13ΪFREQ1��14λ
*/
 void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq)
{
    unsigned long FREQREG = (unsigned long)(268435456.0/AD9834_SYSTEM_COLCK*freq);  //268435456��2^28  ad9834Ƶ�ʼ��㹫ʽΪf=fMCLK/2^28 * FREQREG
    
    unsigned int FREQREG_LSB_14BIT = (unsigned int)FREQREG;
    unsigned int FREQREG_MSB_14BIT = (unsigned int)(FREQREG>>14);
    
    if(freq_number == FREQ_0)
    {
        FREQREG_LSB_14BIT &= ~(1U<<15);
        FREQREG_LSB_14BIT |= 1<<14;
        FREQREG_MSB_14BIT &= ~(1U<<15);
        FREQREG_MSB_14BIT |= 1<<14;
    }
    else
    {
        FREQREG_LSB_14BIT &= ~(1<<14);
        FREQREG_LSB_14BIT |= 1U<<15;
        FREQREG_MSB_14BIT &= ~(1<<14);
        FREQREG_MSB_14BIT |= 1U<<15;
    }
    
    AD9834_Write_16Bits(FREQREG_LSB_14BIT);
    AD9834_Write_16Bits(FREQREG_MSB_14BIT);
    
}
//============================================================//

