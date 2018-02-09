/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
**********������led������ʼ������******************************/

#include "led.h"

/***
��ʼ��LED��IO2_GPIO
**/
void LED_Conf(void)
{
	/***��ʼ���ṹ�壬ʱ�ӣ�����ģʽ���ٶ�***/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED0_GPIO_CLK|LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK|LED4_GPIO_CLK|LED5_GPIO_CLK|LED6_GPIO_CLK|LED7_GPIO_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*****��ʼ��LED0���ص�**************/
	GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
	GPIO_Init(LED0_GPIO_PORT,&GPIO_InitStructure);
	LED0(OFF);
	/*****��ʼ��LED1���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);
	LED1(OFF);
	/*****��ʼ��LED2���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
	GPIO_Init(LED2_GPIO_PORT,&GPIO_InitStructure);
	LED2(OFF);
	/*****��ʼ��LED3���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
	GPIO_Init(LED3_GPIO_PORT,&GPIO_InitStructure);
	LED3(OFF);
	/*****��ʼ��LED4���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED4_GPIO_PIN;
	GPIO_Init(LED4_GPIO_PORT,&GPIO_InitStructure);
	LED4(OFF);
	/*****��ʼ��LED5���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED5_GPIO_PIN;
	GPIO_Init(LED5_GPIO_PORT,&GPIO_InitStructure);
	LED5(OFF);
	/*****��ʼ��LED6���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED6_GPIO_PIN;
	GPIO_Init(LED6_GPIO_PORT,&GPIO_InitStructure);
	LED6(OFF);
	/*****��ʼ��LED7���ص�***************/
	GPIO_InitStructure.GPIO_Pin = LED7_GPIO_PIN;
	GPIO_Init(LED7_GPIO_PORT,&GPIO_InitStructure);
	LED7(OFF);
}

/*
��ʼ������LED
xΪ0��1��2��3��4��5��6��7
*/
void LEDx_Conf(uint8_t LEDx)
{
	switch(LEDx)
	{
		case 0:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED0_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED0_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);	
			break;
		}
		case 1:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED1_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);	
			break;
		}
		case 2:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED2_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED2_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	
			break;
		}
		case 3:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED3_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED3_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);	
			break;
		}
		case 4:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED4_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED4_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED4_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED4_GPIO_PORT, LED4_GPIO_PIN);	
			break;
		}
		case 5:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED5_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED5_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED5_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED5_GPIO_PORT, LED5_GPIO_PIN);	
			break;
		}
		case 6:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED6_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED6_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED6_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED6_GPIO_PORT, LED6_GPIO_PIN);	
			break;
		}
		case 7:
		{
			GPIO_InitTypeDef GPIO_InitStructure;    //����GPIO��ʼ���ṹ��
			RCC_APB2PeriphClockCmd(LED7_GPIO_CLK,ENABLE);    //ʹ��LEDx��ӦGPIO��ʱ��
			//���ó�ʼ���ṹ��
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
			GPIO_InitStructure.GPIO_Pin = LED7_GPIO_PIN;  
			//���ù̼����ʼ��GPIO
			GPIO_Init(LED7_GPIO_PORT,&GPIO_InitStructure);
			//��LEDx
			GPIO_SetBits(LED7_GPIO_PORT, LED7_GPIO_PIN);	
			break;
		}
	}
}

/****************************************************************************
* Function Name  : LED_SetState
* Description    : ����LED��״̬��0������Ӧ��LED������1��ʾ��Ӧ��LEDϨ��
* Input          : stateValue��LED��״̬
* Output         : None
* Return         : None
****************************************************************************/

void LED_ALL_SET(uint8_t stateValue)
{    
    /* ����LED�Ƶ�״̬, GPIOһ������16λ������ֵǿ��ת��λ16λ */
    GPIO_SetBits(GPIOC, (uint16_t)stateValue & 0x00FF);         //��ҪϨ���LEDϨ��
    GPIO_ResetBits(GPIOC, (~(uint16_t)stateValue) & 0x00FF);    //��Ҫ������LED����                  
}


	// ���Դ���ʱִ�еĴ���
void assert_failed(uint8_t* file, uint32_t line)
{
	LED1_ON;
}

