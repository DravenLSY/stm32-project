/*********188������ר��eeprom��д����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
**********��������ģ��I2Cʵ�ֶ�дEEPROM����***************/

#include "eeprom_i2cmoni.h"
#include "i2c_moni.h"



uint16_t EEPROM_ADDRESS;

void EEPROM_Conf(void)
{
	/* ����ͷ�ļ�i2c_ee.h�еĶ�����ѡ��EEPROM���豸��ַ */
#ifdef EEPROM_Block0_ADDRESS
  /* ѡ�� EEPROM Block0 ��д�� */
  EEPROM_ADDRESS = EEPROM_Block0_ADDRESS;
#endif

#ifdef EEPROM_Block1_ADDRESS  
	/* ѡ�� EEPROM Block1 ��д�� */
  EEPROM_ADDRESS = EEPROM_Block1_ADDRESS;
#endif

#ifdef EEPROM_Block2_ADDRESS  
	/* ѡ�� EEPROM Block2 ��д�� */
  EEPROM_ADDRESS = EEPROM_Block2_ADDRESS;
#endif

#ifdef EEPROM_Block3_ADDRESS  
	/* ѡ�� EEPROM Block3 ��д�� */
  EEPROM_ADDRESS = EEPROM_Block3_ADDRESS;
#endif
}



/**
  * @brief  Wait for EEPROM Standby state 
  * @param  ��
  * @retval ��
  */
void EEPROM_I2CMoni_WaitEepromStandbyState(void)      
{
	FunctionalState state;							
  //һֱ������ʼ�źţ�ֱ������Ӧ��
  do
  {
    I2C_Start(); 
    state = MoniI2C_WriteByte(EEPROM_ADDRESS<<1|0);   
	}while(state!=ENABLE);
I2C_Stop();    			
}




/**
  * @brief   дһ���ֽڵ�I2C EEPROM��
  * @param   
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ 
  * @retval  ��
  */
uint32_t EEPROM_I2CMoni_ByteWrite(u8* pBuffer, u8 WriteAddr) 
{
  MoniI2c_WriteByteToSlave(EEPROM_ADDRESS, WriteAddr,* pBuffer);
  return 1;
}




/**
  * @brief   д����ֽڵ�I2C EEPROM��
  * @param   
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ 
  *   @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
uint32_t EEPROM_I2CMoni_BytesWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite) 
{
	uint16_t i;
	uint8_t res;
	for(i=0;i<NumByteToWrite;i++)
	{
		EEPROM_I2CMoni_WaitEepromStandbyState();
		res = MoniI2c_WriteByteToSlave(EEPROM_ADDRESS, WriteAddr,* pBuffer);
	}
	return res;
}




//Ϊ���ٷ������ݣ�ҳ���ͣ�������i2cд�Ĵ�������
uint32_t EEPROM_I2CMoni_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite)
{
	MoniI2c_WriteSomeDataToSlave(EEPROM_ADDRESS,WriteAddr,NumByteToWrite, pBuffer);
	return 0;
}


/**
  * @brief   ���������е�����д��I2C EEPROM��
  * @param   
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
void EEPROM_I2CMoni_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
	u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByteToWrite / I2C_PageSize;
  NumOfSingle = NumByteToWrite % I2C_PageSize;
	
	/* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      EEPROM_I2CMoni_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
        EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, I2C_PageSize); 
    	  EEPROM_I2CMoni_WaitEepromStandbyState();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
      }

      if(NumOfSingle!=0)
      {
        EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        EEPROM_I2CMoni_WaitEepromStandbyState();
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      EEPROM_I2CMoni_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_PageSize;
      NumOfSingle = NumByteToWrite % I2C_PageSize;	
      
      if(count != 0)
      {  
        EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, count);
        EEPROM_I2CMoni_WaitEepromStandbyState();
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        EEPROM_I2CMoni_WaitEepromStandbyState();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;  
      }
      if(NumOfSingle != 0)
      {
        EEPROM_I2CMoni_PageWrite(pBuffer, WriteAddr, NumOfSingle); 
        EEPROM_I2CMoni_WaitEepromStandbyState();
      }
    }
  }  
}

/**
  * @brief   ��EEPROM�����ȡһ������ 
  * @param   
  *		@arg pBuffer:��Ŵ�EEPROM��ȡ�����ݵĻ�����ָ��
  *		@arg WriteAddr:�������ݵ�EEPROM�ĵ�ַ
  *     @arg NumByteToWrite:Ҫ��EEPROM��ȡ���ֽ���
  * @retval  ��
  */
uint32_t I2C_EE_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{  
  MoniI2c_ReadSomeDataFromSlave(EEPROM_ADDRESS,ReadAddr,NumByteToRead, pBuffer);
	return 1;
}




