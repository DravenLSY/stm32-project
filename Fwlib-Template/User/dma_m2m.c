/*********188������ר��dma����****************
**********���ߣ���˼Զ******************
**********�ο�������******************/

#include "dma_m2m.h"

/*

extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];

int main(void)
{	
	USART_Conf();
	
	DMA_M2M_Conf();
	printf("DMA  Init  OK  \n");
	
	 // �ȴ�DMA������� 
  while(DMA_GetFlagStatus(DMA_FLAG_TC)==RESET); 
  
  // �Ƚ�Դ�����봫������� 
  if(Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE))
	{
		printf("���\n");
	}
	else
		printf("�����\n");
  
	while(1);
}


//GPIO�ڴ��䵽����
extern uint8_t aDST_Buffer[BUFFER_SIZE];

int main()
{  	
	LED_Conf();
	
	USART_Conf();
	GPIOA_Conf();

	printf("\n��ʼ����\n");
		
	LED_ALL_ON;
	
	while(1)
	{

		DMA_M2M_Conf();
//     // while(DMA_GetFlagStatus(DMA_FLAG_TC)==RESET); 
////		Clear_DMA_Flag ;	
	  delay_ms(1000);
		LED_ALL_TOGGLE;
//	
//	  Set_DMA_Flag;
	
	}
}

*/



/* ����aSRC_Const_Buffer������ΪDMA��������Դ
 * const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ��������
 * ��ʾ���ݴ洢���ڲ���FLASH��
 */
//const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
//                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
//                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
//                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
//                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
//                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
//                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
//                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
//                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
/* ����DMA����Ŀ��洢��
 * �洢���ڲ���SRAM��																		
 */
uint8_t aDST_Buffer[BUFFER_SIZE]={0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0};
																		
void DMA_M2M_Conf(void)
{
	  DMA_InitTypeDef DMA_InitStructure;
//	  Set_DMA_Flag;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
		// ��ַ1
    DMA_InitStructure.DMA_PeripheralBaseAddr = addr1 ;//(uint32_t)aSRC_Const_Buffer;
		// ��ַ2
		DMA_InitStructure.DMA_MemoryBaseAddr = addr2;
		// ����SRC����ַ1��2��  DST��2��1	
		DMA_InitStructure.DMA_DIR = Derction_2to1;
		// �����С	
		DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
		// ���裨�ڲ���FLASH����ַ����
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMAģʽ��һ�λ���ѭ��ģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
		// ���ȼ�����	
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		// ʹ���ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
		// ����DMAͨ��		   
		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
    
		//���DMA������������ɱ�־λ
    Clear_DMA_Flag ;
	 	Enable_DMA_IRQ	;
		//Set_DMA_CH;
		NVIC_EnableIRQ(DMA_IRQ);
		// ʹ��DMA
		DMA_Cmd(DMA_CHANNEL,ENABLE);
}

/**
  * �ж�ָ�����ȵ���������Դ�Ƿ���ȫ��ȣ�
  * �����ȫ��ȷ���1��ֻҪ����һ�����ݲ���ȷ���0
  */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--)
  {
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer != *pBuffer1)
    {
      /* ��Ӧ����Դ����������˳�������������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer++;
    pBuffer1++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;  
}

//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // �����ַ
//  uint32_t DMA_MemoryBaseAddr;       // �洢����ַ
//  uint32_t DMA_DIR;                  // ���䷽��
//  uint32_t DMA_BufferSize;           // ������Ŀ
//  uint32_t DMA_PeripheralInc;        // �����ַ����ģʽ
//  uint32_t DMA_MemoryInc;            // �洢����ַ����ģʽ
//  uint32_t DMA_PeripheralDataSize;   // �������ݿ��
//  uint32_t DMA_MemoryDataSize;       // �洢�����ݿ��
//  uint32_t DMA_Mode;                 // ģʽѡ��
//  uint32_t DMA_Priority;             // ͨ�����ȼ�
//  uint32_t DMA_M2M;                  // �洢�����洢��ģʽ
//}DMA_InitTypeDef;


