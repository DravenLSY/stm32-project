/***************************************************************************************
									??
#if 1
void lcd_display()	   //LCD��ʼ����ʾ
{
	TFT_ClearScreen(BLACK);
	GUI_Show12ASCII(10,10,"PRECHIN",GREEN,BLACK);
	GUI_Show12ASCII(10,30,"www.prechin.com",GREEN,BLACK);
	GUI_Show12ASCII(10,50,"NRF24L01 Test!",GREEN,BLACK);	
	GUI_Show12ASCII(10,70,"2015-11-13",GREEN,BLACK);	
}

int main(void)
{	
	//delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	TFT_Conf();	
//	TFT_ClearScreen(GREEN);
	
	USART_Conf();
	
	LED_Conf();
	KEY_Conf();
	//button_init();
	NRF_Config();
	//lcd_display();
  LED7_ON;
	while(1);
}

#endif

***************************************************************************************/
#include "nRF.h"


//============================???????==========================================
vu8 sta;									//???STATUS????????
u8 RxBuf[RX_PLOAD_WIDTH];					//???????

extern u8 buttonFlag;						//?????????,?????deal_datapacket.c???
//====================================================================================



/**********************************************************************
???NRF,??IRQ?????EXTI??
***********************************************************************/
void NRF_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_initStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	//???SPI??
	SPI2_Conf();
	SPI_Cmd(SPI2, DISABLE); // SPI���費ʹ��

 	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI����
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//ʱ�����յ�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	//???CE??
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PG13���� ��ֹEN25X�ĸ���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_13);//����
	//??IRQ?????IO?
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	//PB12���� ��ֹ��̫��NSS�ĸ���
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	//��ʼ��ָ��IO
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);//����				
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;	//PF8 9 ���� 	  
 	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��ָ��IO
  	GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_8);//PF6,7,8����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PD3 ����  
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);//PD3����

	EXTI_initStructure.EXTI_Line = NRF_EXTI_Line;
	EXTI_initStructure.EXTI_LineCmd = ENABLE;
	EXTI_initStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_initStructure.EXTI_Trigger = EXTI_Trigger_Falling;					//?????
	EXTI_Init(&EXTI_initStructure);
	
	GPIO_EXTILineConfig(NRF_EXTI_SourcePort,NRF_EXTI_SourcePin);				//??GPIO???????
	NVIC_EnableIRQ(NRF_EXTI_IRQ );
	
	
	CE_LOW;																	//??CE,??:?/?nRF???????CE??,???????????????
	
	//???NRF
 	SPI_Write_Byte(WRITE_REG_CMD + SETUP_AW, 0x03);							//?????????,????0x03,??????5??
	SPI_Write_Buf(WRITE_REG_CMD + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    	//??????????????????NRF????????
	SPI_Write_Buf(WRITE_REG_CMD + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); 	//????????0????????
	SPI_Write_Byte(WRITE_REG_CMD + SETUP_RETR, 0x1a); 						//???????500+86us,????10?
	SPI_Write_Byte(WRITE_REG_CMD + EN_AA, 0x01);      						//?????,?????0????
	SPI_Write_Byte(WRITE_REG_CMD + EN_RXADDR, 0x01);  						//?????0????
	
	//??NRF????????????????????,???????,?????
//	SPI_Write_Byte(WRITE_REG_CMD + SETUP_RETR, 0x00);
//	SPI_Write_Byte(WRITE_REG_CMD + EN_AA, 0x00); 
//	SPI_Write_Byte(WRITE_REG_CMD + EN_RXADDR, 0x00); 
	
	SPI_Write_Byte(WRITE_REG_CMD + RF_SETUP, 0x07);   						//???????1MHZ,????????0dB
	SPI_Write_Byte(WRITE_REG_CMD + RF_CH, 30);        						//????????,????????????????:Fo=(2400+RF-CH)MHz.???????????????2.400-2.525GHz
	SPI_Write_Byte(WRITE_REG_CMD + RX_PW_P0, RX_PLOAD_WIDTH); 				//????????,?????5??,?????????????,????RX_DS??
	
	SPI_Write_Byte(WRITE_REG_CMD + CONFIG, 0x0f);   						//????????

	//??????,??????(???????????,?????????,?????????)
//	printf("SETUP_AW:%x\r\n",SPI_Read_Byte(READ_REG_CMD+SETUP_AW));
//	printf("SETUP_RETR:%x\r\n",SPI_Read_Byte(READ_REG_CMD+SETUP_RETR));
//	printf("EN_RXADDR:%x\r\n",SPI_Read_Byte(READ_REG_CMD+EN_RXADDR));
//	printf("EN_AA:%x\r\n",SPI_Read_Byte(READ_REG_CMD+EN_AA));
//	printf("RF_SETUP:%x\r\n",SPI_Read_Byte(READ_REG_CMD+RF_SETUP));
//	printf("RF_CH:%x\r\n",SPI_Read_Byte(READ_REG_CMD+RF_CH));
//	printf("RX_PW_P0:%x\r\n",SPI_Read_Byte(READ_REG_CMD+RX_PW_P0));
//	printf("CONFIG:%x\r\n",SPI_Read_Byte(READ_REG_CMD+CONFIG));

	CE_HIGH;
}

/*****************************************************************************************
IRQ?????EXTI??????
*******************************************************************************************/
void NRF_EXTI_IRQHandler(void)
{	
	
	NRF24L01_CE = 0;	
	
  NRF_ReceivePacket();	
	
//	sta = SPI_Read_Byte(READ_REG_CMD+STATUS);				
//	if(sta & TX_DS){									
//		RX_Mode();											
//	}else if(sta & RX_DR){
//			 NRF_ReceivePacket();	
//	if(buttonFlag & 0x01){
//			LED1_ON;								
	//	}else{
	//		LED0_TOGGLE;								
		//}
//	}else if(sta & MAX_RT){									
//		RX_Mode();											
//		SPI_Write_Byte(WRITE_REG_CMD+STATUS,sta);		
//	}
	
	EXTI_ClearITPendingBit(NRF_EXTI_Line);
}



/**********************************************************************
??NRF?RX??,????????
***********************************************************************/
void RX_Mode(void)
{
	CE_LOW;													//??CE,??????,?????NRF??????????
	
	SPI_Write_Byte(WRITE_REG_CMD + CONFIG, 0x0f); 			//???????
	SPI_Write_Byte(WRITE_REG_CMD + STATUS, 0x7e);			//?0111 xxxx ?STATUS,????????,??????????????
	
	CE_HIGH; 												//??CE,??????????????
}


/**********************************************************************
?NRF?RX?FIFO????????
????rx_buf:???FIFO?????????????
***********************************************************************/
void NRF_ReceivePacket(void)
{
	CE_LOW;
	
	SPI_Read_Buf(RD_RX_PLOAD,RxBuf,RX_PLOAD_WIDTH);			//?RX??FIFO?????,????????,??:???FIFO?????,NRF??????????
	SPI_Write_Byte(WRITE_REG_CMD+STATUS,sta);   			//??????
	
		//GUI_Show12ASCII(10,90,RxBuf,YELLOW,BLACK);
	
	UnpackData();											//?????????,????,???
	
	CE_HIGH;												//????CE,??????????,?????????
}


/**********************************************************************
??NRF?TX??,????????
????tfbuf:??????????????
***********************************************************************/
void NRF_SendPacket(u8* tfbuf)
{
	CE_LOW;																	//??CE,??????,?????NRF??????????
	
	//SPI_Write_Buf(WRITE_REG_CMD + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 	//???????,????????????,????????NRF???????,??,???????
	SPI_Write_Buf(WR_TX_PLOAD, tfbuf, TX_PLOAD_WIDTH); 						//?????TX??FIFO?,??????TX_PLOAD_WIDTH?????
	
	SPI_Write_Byte(WRITE_REG_CMD + CONFIG, 0x0e); 							//?NRF???????
	SPI_Write_Byte(WRITE_REG_CMD + STATUS, 0x7e);							//?0111 xxxx ?STATUS,????????,??????????????
	
	CE_HIGH;																//??CE,????TX?FIFO????
	
	delay_ms(1);															//CE???,??????130us
}





