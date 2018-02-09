#include "ad5667.h"
#include "include.h"


//��ʼ��IO
void AD5667_Init(void)
{
	   GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin = AD5667_SCL | AD5667_SDA ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_Init(AD5667_GPIO_PORT  ,&GPIO_InitStructure) ;
}

//��ʼ
void AD5667_IIC_START(void)
{
	AD5667_SCL_CLR;
	delay_us(5);
	AD5667_SCL_SET;
	AD5667_SDA_SET;
	delay_us(5);
	AD5667_SDA_CLR;
	delay_us(5);
}

//ֹͣ
void AD5667_IIC_STOP(void)
{
	AD5667_SDA_CLR;
	AD5667_SCL_CLR;
	delay_us(5);
	AD5667_SCL_SET;
	delay_us(5);
	AD5667_SDA_SET;
}

//дһ�ֽ�
//SCL�ߵ�ƽʱSDA������Ч���͵�ƽʱ��������
void AD5667_WRITE_BYTE(unsigned char ch)
{
	int i=0;
	
	AD5667_SCL_CLR;
	delay_us(5);
	
	//��λMSB
	for(i=0;i<8;i++)
	{
		if((ch & 0x80)==1)
			AD5667_SDA_SET;
		else
			AD5667_SDA_CLR;
		
		delay_us(1);
		AD5667_SCL_SET;
		delay_us(5);
		ch <<= 1;
		AD5667_SCL_CLR;
		delay_us(5);
	}
	
	//�ھ�λӦ���ź�
	AD5667_SCL_SET;
	delay_us(5);
}


//д���ֽ�
//voltage = ((dat16 / 65536) * 5) V;
void AD5667_WRITE_REG(unsigned char com , uint16_t dat16)
{
	AD5667_IIC_START();
	
	// 00011110 addr:0001111 WR:0
	AD5667_WRITE_BYTE(0x1e);
	
	//B23~B0 MSB
	AD5667_WRITE_BYTE(com);
	AD5667_WRITE_BYTE(((dat16>>8) & 0xff));
	AD5667_WRITE_BYTE((dat16 & 0xff));
	
	AD5667_IIC_STOP();
}


