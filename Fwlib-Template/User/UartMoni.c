/*
 *
 **********ģ��uart����************************
 **********���ߣ���˼Զ************************
 **********����������51ģ�⴮�����̸ı�********
 **********�������Զ���8λ����λ����У��λ*****
 *
*/
#include "UartMoni.h"
#include "systick.h"

static uint32_t Buad; //�洢�����ʣ�������յ�һ���жϸı�����

uint8_t RxdOrTxd = 0;  //�жϵ�ǰ״̬Ϊ����0����1���ǽ���2
uint8_t RxdEnd = 0;    //���ܽ�����־
uint8_t TxdEnd = 0;    //���ͽ�����־
uint8_t TxdBuf = 0;    //���ͻ�����
uint8_t RxdBuf = 0;    //���ջ�����


//����ģ��uart����ʼ��TX��RX��GPIO����ʼ��SysTick��ʱ��
void UartMoni_Conf(uint32_t buad)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	Buad = buad; //�洢������
	
	//����RX_GPIOΪ��������
	RCC_APB2PeriphClockCmd(TX_GPIO_CLK|RX_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = TX_GPIO_Pin;
	GPIO_Init(TX_GPIO_PORT,&GPIO_InitStructure);
	//����TX_GPIOΪ�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = RX_GPIO_Pin;
	GPIO_Init(TX_GPIO_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(TX_GPIO_PORT,TX_GPIO_Pin);  //���ߵ�ƽ
	//���õδ�ʱ��
	//SysTick_Conf(72000000*Buad);
}


//��ʼ���պ���
void StartRxd(void)
{
	while(GPIO_ReadInputDataBit(RX_GPIO_PORT, RX_GPIO_Pin));    //�ȵ���ʼλ���͵�ƽ��
	SysTick->LOAD  = ((144*Buad)& SysTick_LOAD_RELOAD_Msk) - 1;   //����ʱ��һ�����ڱ�Ϊԭ����һ��
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;  //ʹ�ܵδ�ʱ��
	RxdEnd = 0;     //������ս�����־λ
  RxdOrTxd = 2;   //��־������
}



//�ȴ����պ���
uint8_t RxdData(void)
{
	StartRxd();         //��ʼ����
	while(!RxdEnd);  //�ȵ����ܽ���
	return RxdBuf;
}



//��ʼ���ͺ�����dataҪ���͵�����
void StartTxd(uint8_t data)
{
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
  TxdBuf = data;     //���淢������
  GPIO_SetBits(TX_GPIO_PORT,TX_GPIO_Pin);    //���Ϳ�ʼ,���͵�ƽ
	TxdEnd = 0;     //���㷢�ͽ�����־λ
  RxdOrTxd = 1;	  //��־������
}



/******************��������********************************/
void TxdData(uint8_t data)
{
	StartTxd(data);
	while(!TxdEnd);
}




//�жϷ���������SysTick_Handler����
void UartMoni_Handler(void)
{
	static uint8_t nbit = 0;   //��¼����λ��
	if(RxdOrTxd==1)  //��Ϊ�����ж�
	{
		nbit++;
        if (nbit <= 8)  //��λ��ʼ����8bits
        {
					  TxdBuf & 0x01?GPIO_ResetBits(TX_GPIO_PORT,TX_GPIO_Pin):GPIO_SetBits(TX_GPIO_PORT,TX_GPIO_Pin);
            TxdBuf >>= 1;
        }
        else if (nbit == 9)  //����ֹͣλ
        {
            GPIO_ResetBits(TX_GPIO_PORT,TX_GPIO_Pin);  //����
        }
        else  //���ͽ���
        {
            nbit = 0;    //��ԭλ��¼
            SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;  //ʧ���жϱ�־λ
						RxdOrTxd = 0;   //��־����
            TxdEnd = 1;   //��־���ͽ���
        }
	}
	else if(RxdOrTxd==2)  //��Ϊ�����ж�
	{
		    if (nbit == 0)     //��ʼλ
        {
					  SysTick->LOAD  = ((72*Buad)& SysTick_LOAD_RELOAD_Msk) - 1;   //�ָ�ԭ������
            if (!GPIO_ReadInputDataBit(RX_GPIO_PORT, RX_GPIO_Pin)) //��ʼλ��Ϊ0��������ջ�������׼������
            {
                RxdBuf = 0;
                nbit++;
            }
            else          //��ʼλ��Ϊ0����������
            {
                SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;  //ʧ���жϱ�־λ
						  	RxdOrTxd = 0;   //��־����
            }
        }
        else if (nbit <= 8)   //��λ��ʼ��������λ
        {
            RxdBuf >>= 1;    //�Ƚ�֮ǰ��λ����λ����
            if (GPIO_ReadInputDataBit(RX_GPIO_PORT, RX_GPIO_Pin))     //����Ϊ1ʱ�����λ��1��Ϊ0ʱ��������Ϊ0
            {
                RxdBuf |= 0x80;
            }
            nbit++;
        }
        else  //���ս���
        {
            nbit = 0;         //��ԭλ��¼
            SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;  //ʧ���жϱ�־λ
						RxdOrTxd = 0;   //��־����
            if (GPIO_ReadInputDataBit(RX_GPIO_PORT, RX_GPIO_Pin))     //ֹͣλΪ1������Ϊ������Ч
            {
                RxdEnd = 1;  //��־���ܽ���
            }
        }
	}
}



/****************** ����8λ������ ************************/
void TxdArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    TxdData(array[i]);	
  
  }
	/* �ȴ�������� */
  while(!TxdEnd);
}

/******************����8λ������**********************/
void RxdArray(uint8_t *array, uint16_t num)
{
	 uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����uart��һ���ֽ����� */
	    array[i] = RxdData();	
  }
	 while(!RxdEnd);
}

/*****************  �����ַ��� **********************/
void TxdString(char *str)
{
	unsigned int k=0;
  do 
  {
       TxdData( *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(!TxdEnd);
}

/********************�����ַ���**************************/
void RxdString(char *str)
{
	unsigned int k = 0;
	do
	{
			*(str+k) = RxdData();
		  k++;
	}while(*(str+k)=='\n');
	while(!RxdEnd);
}

/*****************  ����һ��16λ�� **********************/
void TxdHalfWord(uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	TxdData(temp_h);	
	/* ���͵Ͱ�λ */
	TxdData(temp_l);	
}


/********************����һ��16λ����*********************/
void RxdHalfWord(uint16_t *ch)
{
	uint8_t temp_h, temp_l;
	
	temp_h = RxdData();
	temp_l = RxdData();
	
	*ch = temp_h<<8|temp_l;
}


#if 0
#include "stdio.h"
///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		TxdData((uint8_t) ch);
		
		/* �ȴ�������� */
		while(!TxdEnd);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
    while(GPIO_ReadInputDataBit(RX_GPIO_PORT, RX_GPIO_Pin));    //�ȵ���ʼλ���͵�ƽ��
	
		return (int)RxdData();
}
#endif


