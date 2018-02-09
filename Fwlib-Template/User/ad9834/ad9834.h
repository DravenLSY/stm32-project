#ifndef __AD9834_H
#define __AD9834_H

#include "stm32f10x.h"
#include "include.h"


#define Triangle_Wave    0x2002
#define Sine_Wave        0x2028
#define Sine_Cube_Wave   0x2038

/* AD9834����Ƶ�� */
#define AD9834_SYSTEM_COLCK     10000000UL  //10MHz(unsigned long)

/* AD9834 �������� */
#define AD9834_Control_Port     GPIOA
#define AD9834_FSYNC            GPIO_Pin_4
#define AD9834_SCLK             GPIO_Pin_5
#define AD9834_SDATA            GPIO_Pin_7
//#define AD9834_RESET            GPIO_Pin_9
#define AD9834_FSYNC_SET        GPIO_SetBits(AD9834_Control_Port ,AD9834_FSYNC)
#define AD9834_FSYNC_CLR   			GPIO_ResetBits(AD9834_Control_Port ,AD9834_FSYNC)
#define AD9834_SCLK_SET   			GPIO_SetBits(AD9834_Control_Port ,AD9834_SCLK)
#define AD9834_SCLK_CLR   			GPIO_ResetBits(AD9834_Control_Port ,AD9834_SCLK)
#define AD9834_SDATA_SET   			GPIO_SetBits(AD9834_Control_Port ,AD9834_SDATA)
#define AD9834_SDATA_CLR   			GPIO_ResetBits(AD9834_Control_Port ,AD9834_SDATA)
//#define AD9834_RESET_SET   			GPIO_SetBits(AD9834_Control_Port ,AD9834_RESET)
//#define AD9834_RESET_CLR   			GPIO_ResetBits(AD9834_Control_Port ,AD9834_RESET)

#define FREQ_0      0
#define FREQ_1      1


//																					0x2002				0x2028								0x2038       0x0100
//���ƼĴ���λ����                          ���ǲ�      ���Ҳ�(��������)    ���Ҳ�(������)   ��λ
#define DB15        0//                        0            0                     0           0
#define DB14        0//                        0            0                     0           0           
#define DB13        B28//(28λ����д����)      1            1                     1           0          
#define DB12        HLB//(28λ�ֿ�д)          0            0                     0           0           
#define DB11        FSEL//                     0            0                     0           0          
#define DB10        PSEL//                     0            0                     0           0           
#define DB9         PIN_SW//                   0            0                     0           0           //��������ѡ��Ĵ�����ʹ�üĴ���λѡ��Ĵ���
#define DB8         RESET//                    0            0                     0           1           
#define DB7         SLEEP1//                   0            0                     0           0           
#define DB6         SLEEP12//                  0            0                     0           0           
#define DB5         OPBITEN//                  0            1                     1           0           //1��ʹ��SIGN_BIT_OUT���(��ʱMODE����Ϊ0������Ҳ�)
#define DB4         SIGN_PIB//                 0            0                     1           0           //1�����������0�����NCO��MSB
#define DB3         DIV2//                     0            1                     1           0           //0�����MSB����Ƶ��1�����MSB�򷽲�
#define DB2         0//(����)                  0            0                     0           0
#define DB1         MODE//                     1            0                     0           0           //1������ǲ���0������Ҳ�
#define DB0         0//(����)                  0            0                     0           0


/* AD9834�������� */
extern void AD9834_Write_16Bits(unsigned int data) ;  //дһ���ֵ�AD9834
extern void AD9834_Select_Wave(unsigned int initdata) ; //ѡ���������
extern void Init_AD9834(void) ;//��ʼ������
extern void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq) ;//ѡ������Ĵ��������Ƶ��ֵ
void AD9834_Reset(unsigned int initdata);  //��λad9834�ڲ��Ĵ���

#endif /* AD9834_H */
