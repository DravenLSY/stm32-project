#ifndef __OLED_SSD1306_SPI_8080_H
#define __OLED_SSD1306_SPI_8080_H


#include "stm32f10x.h"
#include "stdlib.h"	
#include "gpio.h"


//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
//2:IICģʽ
#define OLED_MODE 0


#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64


#if OLED_MODE==0
//OLDE-IIC���߿��ƹܽŶ���
#define OLED_CS   PDout(3)		
#define OLED_RST  PDout(4)
#define OLED_DC   PDout(5)
#define OLED_SCL  PDout(6)
#define OLED_SDA  PDout(7)
#endif


#if OLED_MODE==1
//OLDE-8080���߿��ƹܽŶ���
#define OLED_CS   PDout(3)		
#define OLED_RST  PDout(4)
#define OLED_DC   PDout(5)
#define OLED_WR   PDout(6)
#define OLED_RD   PDout(7)

#define OLED_DATA_OUT(x) GPIO_Write(GPIOC,x);//���
#endif


#if OLED_MODE==2
//OLDE-SPI4�߿��ƹܽŶ���

#endif


 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����		    						  



//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Set_Pos(unsigned char x, unsigned char y);	   							   		    

void OLED_Conf(void);
void OLED_Display_On(void);//����OLED��ʾ
void OLED_Display_Off(void);//�ر�OLED��ʾ
void OLED_Refresh_Gram(void);//�����Դ浽LCD		
void OLED_Clear(void);//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_DrawPoint(u8 x,u8 y,u8 t);//����
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//x1,y1,x2,y2 ���Խ����������
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//��ָ��λ����ʾһ���ַ�,���������ַ�
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//��ʾ2������
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//��ʾ�ַ��� 
void OLED_ShowFontHZ(u8 x,u8 y,u8 pos,u8 size,u8 mode);//��ʾ����
void OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[]);//��ʾBMPͼƬ128��64






#endif


