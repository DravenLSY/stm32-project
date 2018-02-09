/*********188������ר��Ӳ��iic����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
**********��������Ϊͨ��Ӳ��IIC������eeprom***********/

#include "i2c_hard.h"
#include "usart.h"	

static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;   

/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode��������룬����������λ���ĸ����ڳ���.
  * @retval ����0����ʾIIC��ȡʧ��.
  */
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
  I2C_ERROR("I2C �ȴ���ʱ!errorCode = %d",errorCode);
  return 0;
}



/**
  * @brief  I2C I/O����
  * @param  ��
  * @retval ��
  */
static void I2C_GPIO_Conf(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* ʹ���� I2C �йص�ʱ�� */
	RCC_APB1PeriphClockCmd( I2C_CLK, ENABLE );
	RCC_APB2PeriphClockCmd( I2C_GPIO_CLK, ENABLE );
	
    
  /* I2C_SCL��I2C_SDA*/
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);		
}



/**
  * @brief  I2C ����ģʽ����
  * @param  ��
  * @retval ��
  */
static void I2C_Mode_Conf(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	 
	/* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* ͨ������ */
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
	/* I2C ��ʼ�� */
  I2C_Init(I2Cx_Hard, &I2C_InitStructure);
  
	/* ʹ�� I2C */
  I2C_Cmd(I2Cx_Hard, ENABLE);   
}



void I2C_Hard_Conf(void)
{
  I2C_GPIO_Conf();  
  I2C_Mode_Conf();
}


/*
  �ٷ��⺯��
	void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
	void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
  void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
  void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
	uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
	void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);
	uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);
	FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
*/



uint32_t I2C_ByteWrite_ToRegister(u8* pBuffer, uint16_t ADDR ,u8 WriteAddr) 
{
	//��������Ƿ����
  while(I2C_GetFlagStatus(I2Cx_Hard, I2C_FLAG_BUSY))   
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  } 
	
	//��ʼI2C�������EV5
	I2CTimeout = I2CT_LONG_TIMEOUT;
	I2C_GenerateSTART(I2Cx_Hard, ENABLE);
	while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  } 
	
	
	//�����豸��ַ�����EV6
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	I2C_Send7bitAddress(I2Cx_Hard, ADDR, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
  }  


	//����д��Ĵ�����ַ�����EV8
	 I2CTimeout = I2CT_FLAG_TIMEOUT;
	 I2C_SendData(I2Cx_Hard, WriteAddr);   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
  } 
	
	 //����Ҫд������ݲ����EV8
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
  I2C_SendData(I2Cx_Hard, *pBuffer);  
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
  } 
  
  //I2Cֹͣ
  I2C_GenerateSTOP(I2Cx_Hard, ENABLE);
  
  return 1;
}
	

/**
  * @brief   ���豸�����ȡһ������ 
  * @param   
  *		@arg pBuffer:��Ŵ��豸��ȡ�����ݵĻ�����ָ��
  *		@arg WriteAddr:�������ݵ��豸�ĵ�ַ
  *     @arg NumByteToWrite:Ҫ���豸��ȡ���ֽ���
  * @retval  ��
  */
uint32_t I2C_Read_FromRegister(u8* pBuffer, uint16_t ADDR,u8 ReadAddr, u16 NumByteToRead)
{  
	I2CTimeout = I2CT_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2Cx_Hard, I2C_FLAG_BUSY))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
   }
  
  //��ʼI2C�����EV5
	I2CTimeout = I2CT_LONG_TIMEOUT;
  I2C_GenerateSTART(I2Cx_Hard, ENABLE);  
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
   }
 
	 
  //�����豸��ַ�����EV6
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  I2C_Send7bitAddress(I2Cx_Hard, ADDR, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
   }
    
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2Cx_Hard, ENABLE);


  //����Ҫ���ļĴ�����ַ�����EV8	 
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  I2C_SendData(I2Cx_Hard, ReadAddr);   
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
   }
 
   
 //I2C��ʼ�����EV5 
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  I2C_GenerateSTART(I2Cx_Hard, ENABLE);  
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
   }
    
  //�����豸��ַ������򲢼��EV6	   
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  I2C_Send7bitAddress(I2Cx_Hard, ADDR, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
   }
  
  //��ȡ���ֽ�����
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      //ʧ��Ӧ��
      I2C_AcknowledgeConfig(I2Cx_Hard, DISABLE);
      
      //I2Cֹͣ
      I2C_GenerateSTOP(I2Cx_Hard, ENABLE);
    }

    //���EV7   
    I2CTimeout = I2CT_LONG_TIMEOUT;   
		while(I2C_CheckEvent(I2Cx_Hard, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  
		{
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
		} 
    {      
      //��һ���ֽ�
      *pBuffer = I2C_ReceiveData(I2Cx_Hard);
      pBuffer++; 
      NumByteToRead--;        
    }   
  }

  //ʹ��Ӧ���Ա��´ζ�ȡ
  I2C_AcknowledgeConfig(I2Cx_Hard, ENABLE);
  
    return 1;
}

	


