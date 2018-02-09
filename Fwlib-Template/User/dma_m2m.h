#ifndef __DMA_M2M_H
#define __DMA_M2M_H

// DMA-�洢�����洢��ģʽ �����ڲ���FLASH���ڲ���SRAM
	
#include "stm32f10x.h"
#include "led.h"






//DMA��ַ
#define     addr1            (uint32_t)aDST_Buffer
#define     addr2            GPIOC_BASE+0x0C

//���䷽��
#define     Derction_1to2    DMA_DIR_PeripheralSRC
#define     Derction_2to1    DMA_DIR_PeripheralDST

// Ҫ���͵����ݴ�С
#define BUFFER_SIZE     8




// ��ʹ�ô洢�����洢��ģʽʱ��ͨ���������ѡ��û��Ӳ�ԵĹ涨
#define DMA_CHANNEL     DMA1_Channel6
#define DMA_CLOCK       RCC_AHBPeriph_DMA1

// ������ɱ�־
#define DMA_FLAG_TC     DMA1_FLAG_TC6



void DMA_M2M_Conf(void);		
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);

//#define Set_DMA_Flag                    DMA1 ->IFCR &= 0xf0fffff//��������ж�ͨ��
#define Enable_DMA_IRQ		              DMA_CHANNEL ->CCR |= 0x0f//��������ж�
#define Disable_DMA_IRQ                 DMA_CHANNEL ->CCR &= 0xfff0//�ر�����ж�
#define Clear_DMA_Flag                  DMA1->IFCR |= 0xf00000 //���DMA��ɱ�־λ
#define DMA_Handler                     DMA1_Channel6_IRQHandler          //�жϷ����� 
#define DMA_IRQ                         DMA1_Channel6_IRQn
#define DMA_Finish       DMA_GetFlagStatus(DMA_FLAG_TC)==RESET



#endif


