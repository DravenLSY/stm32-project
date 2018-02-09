#ifndef _OV7725_EAGLE_H_
#define _OV7725_EAGLE_H_

#include "ov7725_reg.h"
#include "stm32f10x.h"


#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )
typedef struct
{
    u8 addr;                 /*�Ĵ�����ַ*/
    u8 val;                   /*�Ĵ���ֵ*/
} reg_s;

//????????
typedef enum
{
    IMG_NOTINIT = 0,
    IMG_FINISH,             //ͼ��ɼ����
    IMG_FAIL,               //ͼ��ɼ�ʧ��(�ɼ���������)
    IMG_GATHER,             //ͼ��ɼ���
    IMG_START,              //��ʼ�ɼ�ͼ��
    IMG_STOP,               //��ֹ�ɼ�ͼ��
} IMG_STATUS_e;





#define CAMERA_USE_HREF     0          //�Ƿ�ʹ�����жϣ�1ʹ�� 0����  
#define CAMERA_COLOR        0          //����ͷͼ��ģʽ��0��ֵ�� 1�Ҷ� 2RGB565     
#define CAMERA_POWER        0          //����ͷ��Դѡ��0(3.3V) 1(5V)     

//����ͷAPI�ӿ�
#define camera_init(imgaddr)    ov7725_eagle_init(imgaddr)
#define camera_get_img()        ov7725_eagle_get_img()


#define camera_vsync()          ov7725_eagle_vsync()
#define camera_href()           ov7725_eagle_href()
#define camera_dma()            ov7725_eagle_dma()

//�ϲ��װ
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH      
#define CAMERA_W            OV7725_EAGLE_W           
#define CAMERA_H            OV7725_EAGLE_H            

#define CAMERA_SIZE         OV7725_EAGLE_SIZE           
#define CAMERA_DMA_NUM      CAMERA_SIZE       

 

//����ͷ����             
#define OV7725_EAGLE_W            80                       //����ͷͼ����            
#define OV7725_EAGLE_H            60                         //����ͷͼ��߶�          
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )   //ͼ��ռ�ÿռ��С



/************************** OV7725 �������Ŷ���********************************/
// RCLK����DMA��ʼ�ж�
#define      EAGLE_RCLK_GPIO_CLK                     RCC_APB2Periph_GPIOA
#define      EAGLE_RCLK_GPIO_PORT                    GPIOA
#define      EAGLE_RCLK_GPIO_PIN                     GPIO_Pin_0

#define      EAGLE_RCLK_EXTI_SOURCE_PORT            GPIO_PortSourceGPIOA
#define      EAGLE_RCLK_EXTI_SOURCE_PIN             GPIO_PinSource0
#define      EAGLE_RCLK_EXTI_LINE                   EXTI_Line0
#define      EAGLE_RCLK_EXTI_IRQ                    EXTI0_IRQn
#define      EAGLE_RCLK_EXTI_INT_FUNCTION           EXTI0_IRQHandler

// 8λ���ݿ�
#define      EAGLE_DATA_GPIO_CLK                     RCC_APB2Periph_GPIOF
#define      EAGLE_DATA_GPIO_PORT                    GPIOF
#define      EAGLE_DATA_0_GPIO_PIN                   GPIO_Pin_0
#define      EAGLE_DATA_1_GPIO_PIN                   GPIO_Pin_1
#define      EAGLE_DATA_2_GPIO_PIN                   GPIO_Pin_2
#define      EAGLE_DATA_3_GPIO_PIN                   GPIO_Pin_3
#define      EAGLE_DATA_4_GPIO_PIN                   GPIO_Pin_4
#define      EAGLE_DATA_5_GPIO_PIN                   GPIO_Pin_5
#define      EAGLE_DATA_6_GPIO_PIN                   GPIO_Pin_6
#define      EAGLE_DATA_7_GPIO_PIN                   GPIO_Pin_7

// OV7725���ж�
#define      EAGLE_VSYNC_GPIO_CLK                    RCC_APB2Periph_GPIOA
#define      EAGLE_VSYNC_GPIO_PORT                   GPIOA
#define      EAGLE_VSYNC_GPIO_PIN                    GPIO_Pin_4

#define      EAGLE_VSYNC_EXTI_SOURCE_PORT            GPIO_PortSourceGPIOA
#define      EAGLE_VSYNC_EXTI_SOURCE_PIN             GPIO_PinSource4
#define      EAGLE_VSYNC_EXTI_LINE                   EXTI_Line4
#define      EAGLE_VSYNC_EXTI_IRQ                    EXTI4_IRQn
#define      EAGLE_VSYNC_EXTI_INT_FUNCTION           EXTI4_IRQHandler







//DMA����
#define OV7725_EAGLE_DMA_CH                   DMA1_Channel6             //DMA�ɼ�ͨ��   
#define OV7725_EAGLE_DMA_Finish               DMA_GetFlagStatus(DMA_FLAG_TC)==RESET
// ��ʹ�ô洢�����洢��ģʽʱ��ͨ���������ѡ��û��Ӳ�ԵĹ涨    
#define OV7725_EAGLE_DMA_CLOCK                RCC_AHBPeriph_DMA1
// ������ɱ�־
#define OV7725_EAGLE_DMA_FLAG_TC              DMA1_FLAG_TC6
//���δ�������
#define OV7725_EAGLE_BUFFER_SIZE              1

//DMA��������ж�����
//#define Set_DMA_FINISH_Flag                 DMA1 ->IFCR &= 0xf0fffff//��������ж�ͨ��
#define Enable_DMA_FINISH_IRQ		              OV7725_EAGLE_DMA_CH ->CCR |= 0x0f//��������ж�
#define Disable_DMA_FINISH_IRQ                OV7725_EAGLE_DMA_CH ->CCR &= 0xfff0//�ر�����ж�
#define Clear_DMA_FINISH_Flag                 DMA1->IFCR |= 0xf00000   //���DMA��ɱ�־λ
#define EAGLE_DMA_Handler                     DMA1_Channel6_IRQHandler          //�жϷ����� 
#define EAGLE_DMA_IRQ                         DMA1_Channel6_IRQn







void OV7725_EAGLE_DMA_Conf(void);
u8 OV7725_Eagle_Conf(u8 *imgaddr);
void OV7725_Eagle_Get_Img(void);
void img_extract(void *dst, void *src, uint32_t srclen);




#endif 


