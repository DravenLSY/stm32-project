/*********188������ר��key����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
**********������KEY������ʼ�������Լ����β�ͬ���Ͱ�����Ӳ���ӿ�******************************/

#include "key.h"
#include "systick.h"
/*
��ʼ�����а���
*/
void KEY_Conf(void)
{
	//����GPIO���ͽṹ�壬��ʼ��GPIOʱ��
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEYUP_GPIO_CLK|KEY0_GPIO_CLK|KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);
	//��ʼ��KEYUPΪ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
	GPIO_InitStructure.GPIO_Pin = KEYUP_GPIO_PIN;
	GPIO_Init(KEYUP_GPIO_PORT,&GPIO_InitStructure);
	//��ʼ��KEY0Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);
  //��ʼ��KEY1Ϊ��������
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);
	//��ʼ��KEY2Ϊ��������
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);
}

/*
��ʼ������KEY
xΪ0��1��2
*/
void KEYUP_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEYUP_GPIO_CLK,ENABLE);
		//��ʼ��KEYUPΪ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_InitStructure.GPIO_Pin = KEYUP_GPIO_PIN;
	GPIO_Init(KEYUP_GPIO_PORT,&GPIO_InitStructure);
}
void KEYx_Conf(uint8_t x)
{
	switch(x)
	{
		case 0:
		{
			//����GPIO���ͽṹ�壬��ʼ��GPIOʱ��
			GPIO_InitTypeDef GPIO_InitStructure;
			//�жϰ�������
			RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK,ENABLE);
			//��ʼ��KEYxΪ��������
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
			GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;
			GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);
			break;
		}
		case 1:
		{
			//����GPIO���ͽṹ�壬��ʼ��GPIOʱ��
			GPIO_InitTypeDef GPIO_InitStructure;
			//�жϰ�������
			RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
			//��ʼ��KEYxΪ��������
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
			GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
			GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);
			break;
		}
		case 2:
		{
			//����GPIO���ͽṹ�壬��ʼ��GPIOʱ��
			GPIO_InitTypeDef GPIO_InitStructure;
			//�жϰ�������
			RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK,ENABLE);
			//��ʼ��KEYxΪ��������
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
			GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
			GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);
			break;
		}
	}
}

/*
���KEYUP
xΪUP��0��1��2
*/

uint8_t KEYUP_Scan(void)
{
	if(GPIO_ReadInputDataBit(KEYUP_GPIO_PORT, KEYUP_GPIO_PIN) == KEYUP_ON)
		{
			while(GPIO_ReadInputDataBit(KEYUP_GPIO_PORT, KEYUP_GPIO_PIN) == KEYUP_ON);
			return KEYUP_ON;	
		}
	else
		  return KEYUP_OFF;
}

uint8_t KEYx_Scan(uint8_t x)
{
	switch(x)
	{
		case 0:
		{
			if(GPIO_ReadInputDataBit(KEY0_GPIO_PORT,KEY0_GPIO_PIN	) == KEY_ON)
			{
				while(GPIO_ReadInputDataBit(KEY0_GPIO_PORT,KEY0_GPIO_PIN	) == KEY_ON);
				return KEY_ON;	
			}
		  else
			  return KEY_OFF;
		}
		case 1:
		{
			if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN	) == KEY_ON)
			{
				while(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN	) == KEY_ON);
				return KEY_ON;	
			}
		  else
			  return KEY_OFF;
		}
		case 2:
		{
			if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PIN	) == KEY_ON)
			{
				while(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PIN	) == KEY_ON);
				return KEY_ON;	
			}
		  else
			  return KEY_OFF;
		}
		default:return 0;
	}
}


uint8_t KEY_Scan(void)
{
       uint8_t keyValue = 0;

    if((KEYUP == KEYUP_ON) || (KEY0 == KEY_ON) || (KEY1 == KEY_ON) || (KEY2 == KEY_ON)) //����Ƿ��а�������
    {
        delay_ms(10);                                      //��ʱ����

        /* ������ĸ��������� */
        if(KEYUP == KEYUP_ON)
        {
            keyValue = KEY_UP;
        }
        else if(KEY0 == KEY_ON)
        {
            keyValue = KEY_LEFT;
        }
        else if(KEY1 == KEY_ON)
        {
            keyValue = KEY_DOWN;
        }
        else if(KEY2 == KEY_ON)
        {
            keyValue = KEY_RIGHT;
        }
        else
        {
            keyValue = 0;
        }
        
        /* �а�������ʱ�������ּ�� */
        if(keyValue != 0)
        {
            while(((KEYUP == KEYUP_ON) || (KEY0 == KEY_ON) || (KEY1 == KEY_ON) || (KEY2 == KEY_ON)));
//            delay_ms(10); //�����������г�����٣�����ɨ����ٶ�̫�죬��һ�����������������   
        }        
    }

    return keyValue;
}


