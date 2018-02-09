//r61509v
/*
int main(void)
{
	LEDx_Conf(1);              
	TFT_Conf();	  //TFT������ʼ��
	TFT_ClearScreen(BLACK);	 //����
	GUI_Show12ASCII(80,130,(uint8_t*)"hello world!",YELLOW,BLACK);
	while(1)
	{		
			LED1_ON;
	}
}
*/
#include "lcd_driver.h"
#include "systick.h"

/****************************************************************************
*��������TFT_GPIO_Config
*��  �룺��
*��  ������
*��  �ܣ���ʼ��TFT��IO�ڡ�
****************************************************************************/	  

void TFT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ��ʱ��ʹ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE  
	                      | RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	/* FSMC_A10(G12) ��RS��G0��*/
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 
	                              | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_8 
								  | GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_11
								  | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
								  | GPIO_Pin_15 );

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
	                               | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
								   | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/****************************************************************************
* Function Name  : TFT_FSMC_Config
* Description    : ��ʼ��FSMC
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void TFT_FSMC_Config(void)
{
	/* ��ʼ������ */
	FSMC_NORSRAMInitTypeDef        FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTiming;

	
	/* ���ö�дʱ�򣬸�FSMC_NORSRAMInitStructure���� */
	/* ��ַ����ʱ�䣬4��HCLK���� */
	FSMC_NORSRAMTiming.FSMC_AddressSetupTime = 0x03;

	/* ��ַ����ʱ�䣬1��HCLK���� */
	FSMC_NORSRAMTiming.FSMC_AddressHoldTime = 0x00;

	/* ���ݽ���ʱ�䣬6��HCLK���� */
	FSMC_NORSRAMTiming.FSMC_DataSetupTime = 0x05;

	/* ���ݱ���ʱ�䣬1��HCLK���� */
	FSMC_NORSRAMTiming.FSMC_DataLatency = 0x00;

	/* ���߻ָ�ʱ������ */
	FSMC_NORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
	
	/* ʱ�ӷ�Ƶ���� */
	FSMC_NORSRAMTiming.FSMC_CLKDivision = 0x01;

	/* ����ģʽ������ڵ�ַ/���ݲ�����ʱ��ABCDģʽ�����𲻴� */
	FSMC_NORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_B;

	/*����FSMC_NORSRAMInitStructure������*/
	/* FSMC���ĸ��洢�飨bank��������ʹ�õ�һ����bank1�� */
	/* ͬʱ����ʹ�õ���bank����ĵ� 4��RAM�� */
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;

	/* ��������ʹ��SRAMģʽ */
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;

	/* ʹ�õ����ݿ��Ϊ16λ */
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;

	/* ����дʹ�ܴ� */
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;

	/* ѡ����չģʽʹ�ܣ������ö���д�ò�ͬ��ʱ�� */
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
	
	/* ���õ�ַ�����ݸ���ʹ�ܲ��� */
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	
	/* ���ö�дʱ�� */
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTiming;
	
	/* ����дʱ�� */
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTiming;

	/* ��FSMC��ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  
	/*!< Enable FSMC Bank1_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);	
	
}

/****************************************************************************
* Function Name  : TFT_WriteCmd
* Description    : LCDд������
* Input          : cmd��д���16λ����
* Output         : None
* Return         : None
****************************************************************************/

void TFT_WriteCmd(uint16_t cmd)
{
	TFT->TFT_CMD = cmd ;
}

/****************************************************************************
* Function Name  : TFT_WriteData
* Description    : LCDд������
* Input          : dat��д���16λ����
* Output         : None
* Return         : None
****************************************************************************/

void TFT_WriteData(u16 dat)
{
	TFT->TFT_DATA = dat;
}

void TFT_WriteData_Color(u16 color)
{
//	  color = ((color >> 1) & 0x55555555) | ((color << 1) & 0xaaaaaaaa); 
//    color = ((color >> 2) & 0x33333333) | ((color << 2) & 0xcccccccc); 
//    color = ((color >> 4) & 0x0f0f0f0f) | ((color << 4) & 0xf0f0f0f0); 
//    color = ((color >> 8) & 0x00ff00ff) | ((color << 8) & 0xff00ff00); 
	TFT->TFT_DATA = color;
}

void LCD_WriteCmdData(u16 cmd,u16 data)
{
	TFT_WriteCmd(cmd);
	TFT_WriteData(data);
}

/****************************************************************************
* Function Name  : TFT_Init
* Description    : ��ʼ��LCD��
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void TFT_Conf(void)
{
	uint16_t i;

	TFT_GPIO_Config();
	TFT_FSMC_Config();

	delay_ms(50); 

	
	TFT_WriteCmd(0x0000);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0000);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0000);TFT_WriteData(0x0000);
	
	TFT_WriteCmd(0x0400);TFT_WriteData(0x6200); //base image ����400��
	TFT_WriteCmd(0x0008);TFT_WriteData(0x0808); 


	TFT_WriteCmd(0x0001);TFT_WriteData(0x0100);  //������ʾ����base image�Ĺ��뿪
 	TFT_WriteCmd(0x0002);TFT_WriteData(0x0100);
	TFT_WriteCmd(0x0003);TFT_WriteData(0x5030/*0x1030*/);  //0x5030 RGB��Ϊ5-6-5ģʽ
	TFT_WriteCmd(0x0008);TFT_WriteData(0x0808);
	/*gamma set 20090423 BY LYJ*/

	 TFT_WriteCmd(0x0300);TFT_WriteData(0x000c); 
	 TFT_WriteCmd(0x0301);TFT_WriteData(0x5A0B); 
	 TFT_WriteCmd(0x0302);TFT_WriteData(0x0906); 
	 TFT_WriteCmd(0x0303);TFT_WriteData(0x1017); 
	 TFT_WriteCmd(0x0304);TFT_WriteData(0x2300); 
	 TFT_WriteCmd(0x0305);TFT_WriteData(0x1700); 
	 TFT_WriteCmd(0x0306);TFT_WriteData(0x6309); 
	 TFT_WriteCmd(0x0307);TFT_WriteData(0x0c09); 
	 TFT_WriteCmd(0x0308);TFT_WriteData(0x100c); 
	 TFT_WriteCmd(0x0309);TFT_WriteData(0x2232); 
	 /*power set*/
	  TFT_WriteCmd(0x0010);TFT_WriteData(0x0014);//0x0019���Ƶ��
	  TFT_WriteCmd(0x0011);TFT_WriteData(0x0101);  
	  TFT_WriteCmd(0x0100);TFT_WriteData(0x0230);//0x330���õ�Դ���ƣ�ƽ����ʾ�������
		//for(i=500; i>0; i--);
		delay_ms(50);
	  TFT_WriteCmd(0x0101);TFT_WriteData(0x0247);//
		for(i=500; i>0; i--);
		delay_ms(50);
	  TFT_WriteCmd(0x0103);TFT_WriteData(0x0a00);//Starts VLOUT3,Sets the VREG1OUT.
		for(i=500; i>0; i--);
		delay_ms(10);
	  TFT_WriteCmd(0x0280);TFT_WriteData(0xf0ff);//0xbf00 VCOMH voltage   //0xcEff
		delay_ms(50);
		for(i=500; i>0; i--);
	  TFT_WriteCmd(0x0102);TFT_WriteData(0xB1b0);//Starts VLOUT3,Sets the VREG1OUT.
		for(i=500; i>0; i--);                      //0xd1b0 PSON��PON����Ϊ1����Դ��Ӧ��
		delay_ms(50);
	 /*window set*/
	  TFT_WriteCmd(0x0210);TFT_WriteData(0x0000);//Window Horizontal RAM Address Start
	  TFT_WriteCmd(0x0211);TFT_WriteData(0x00ef);//Window Horizontal RAM Address End
	  TFT_WriteCmd(0x0212);TFT_WriteData(0x0000);//Window Vertical RAM Address Start
	  TFT_WriteCmd(0x0213);TFT_WriteData(0x018f);//Window Vertical RAM Address End
	  TFT_WriteCmd(0x0200);TFT_WriteData(0x0000);//RAM Address Set (Horizontal Address)
	  TFT_WriteCmd(0x0201);TFT_WriteData(0x0000);//RAM Address Set (Vertical Address)
	  TFT_WriteCmd(0x0401);TFT_WriteData(0x0000);//Base Image Display 0x01 ����base image����ģʽ����������
	  TFT_WriteCmd(0x0007);TFT_WriteData(0x0100);//Display Control 1
		for(i=500; i>0; i--);
		delay_ms(50);
	  TFT_WriteCmd(0x0202);
}

/****************************************************************************
* Function Name  : TFT_SetWindow
* Description    : ����Ҫ�����Ĵ��ڷ�Χ
* Input          : xStart��������ʼX����
*                * yStart��������ʼY����
*                * xEnd�����ڽ���X����
*                * yEnd�����ڽ���Y����
* Output         : None
* Return         : None
****************************************************************************/

void TFT_SetWindow(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd)
{	
	LCD_WriteCmdData(0x0210, xStart);	 //ˮƽ����ʼ
	LCD_WriteCmdData(0x0211, xEnd);	     //ˮƽ�߽���
	LCD_WriteCmdData(0x0212, yStart);	 //��ֱ����ʼ
	LCD_WriteCmdData(0x0213, yEnd);	     //��ֱ�߽���

	LCD_WriteCmdData(0x0200,xStart);
	LCD_WriteCmdData(0x0201,yStart);

	TFT_WriteCmd(0x0202); 
}

/****************************************************************************
* Function Name  : TFT_ClearScreen
* Description    : ��LCD��������Ӧ����ɫ
* Input          : color��������ɫ
* Output         : None
* Return         : None
****************************************************************************/
	  
void TFT_ClearScreen(uint16_t color)
{
 	uint16_t i, j ;

	TFT_SetWindow(0, 0, TFT_XMAX, TFT_YMAX);	 //��������
  	for(i=0; i<TFT_XMAX+1; i++)
	{
		for (j=0; j<TFT_YMAX+1; j++)
		{
			TFT_WriteData_Color(color);
		}
	}
}
