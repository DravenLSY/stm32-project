/*********188������ר��key����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
**********������KEY������ʼ�������Լ����β�ͬ���Ͱ�����Ӳ���ӿ�******************************/

#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

//��������

#define    KEYUP_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEYUP_GPIO_PORT    GPIOA			   
#define    KEYUP_GPIO_PIN		 GPIO_Pin_0

#define    KEY0_GPIO_CLK     RCC_APB2Periph_GPIOE
#define    KEY0_GPIO_PORT    GPIOE			   
#define    KEY0_GPIO_PIN		 GPIO_Pin_2

#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOE
#define    KEY1_GPIO_PORT    GPIOE			   
#define    KEY1_GPIO_PIN		 GPIO_Pin_3

#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOE
#define    KEY2_GPIO_PORT    GPIOE			   
#define    KEY2_GPIO_PIN		 GPIO_Pin_4

//�����������Ŀ���
#define KEYUP_ON 1
#define KEYUP_OFF 0
#define KEY_ON 0
#define KEY_OFF 1

/* ������ȡ */
#define KEYUP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)

/* ���尴���ļ�ֵ */
#define KEY_UP    0x01
#define KEY_DOWN  0x02
#define KEY_LEFT  0x04
#define KEY_RIGHT 0x08
#define KEY_ALL   0x0F

//������ʼ����ɨ�躯��
void KEY_Conf(void);
#define key_init  KEY_Conf  
void KEYUP_Conf(void);
void KEYx_Conf(uint8_t x);
uint8_t KEYUP_Scan(void);
uint8_t KEYx_Scan(uint8_t x);
uint8_t KEY_Scan(void);

#endif

