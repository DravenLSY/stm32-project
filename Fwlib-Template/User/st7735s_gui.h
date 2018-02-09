#ifndef __ST7735S_GUI_H
#define __ST7735S_GUI_H

#include "stm32f10x.h"
#include "st7735s_lcd.h"
#include "ASCII.h"
#include "lcd_driver.h"

#ifndef __SITE__
#define __SITE__
/*
 * ��������ṹ��
 */
typedef struct
{
    u16 x;
    u16 y;
} Site_t;

/*
 * ��������С�ṹ��
 */
typedef struct
{
    u16 W;       
    u16 H;       
} Size_t;
#endif


/******????*****/
//#define RED     0XF800    //??
//#define GREEN   0X07E0    //??
//#define BLUE    0X001F    //??
//#define BRED    0XF81F
//#define GRED    0XFFE0    //??
//#define GBLUE   0X07FF    //
//#define BLACK   0X0000    //??
//#define WHITE   0XFFFF    //??
//#define YELLOW  0xFFE0    //??

#define FCOLOUR         WHITE    //??????
#define BCOLOUR         BLACK     //??????

//??RGB?3??,rgb565???16?
#define RGB565_R(rgb565)                ((u8)(((u16)(rgb565)>>11) &0x1F))
#define RGB565_G(rgb565)                ((u8)(((u16)(rgb565)>> 5) &0x3F))
#define RGB565_B(rgb565)                ((u8)( (u16)(rgb565)      &0x1F))


#define GRAY_2_RGB565(gray)             ((u16)((((u8)(gray)>>3)<<11)|(((u8)(gray)>>2)<<5)|((u8)(gray)>>3)))

#define RGB565_2_GRAY(rgb565)           ((u8)(((RGB565_R(rgb565)*235+RGB565_G(rgb565)*613+RGB565_B(rgb565)*625)+1)>>8))  //  31*235+63*613+31*625+1  = 255*256


#define RGB565_H(rgb565)                ((u8)(((u16)(rgb565))>>8))
#define RGB565_L(rgb565)                (u8)(rgb565))

#define RGB24_RGB565(R,G,B)             ((u16)((((u8)(R)>>3)<<11)|(((u8)(G)>>2)<<5)|((u8)(B)>>3)))
#define RGB555_RGB565(rgb555)           (((((u16)(rgb555)) & (u16)(~0x1F)) << 1) |  (((u16)(rgb555)) & 0x1F))
#define BGR555_RGB565(bgr555)           ((((u16)(bgr555)<<11) & (u16)(0x1F<<11)) | (((u16)(bgr555)) & (u16)(0x1F<<5)) | (((u16)(bgr555)>>10) & (u16)(0x1F)))



//????????????:
//LCD_H                         //?
//LCD_W                         //?

//LCD_INIT()                    //???
//LCD_PTLON(site,size)          //??
//LCD_RAMWR()                   //???
//LCD_WR_DATA(data)             //???
//LCD_WR_DATA_B(data)           //???(??),16????LCD_WR_DATA????,8???????

//?????
//LCD_RAMRD()                   //???
//LCD_SET_DIR(opt)              //??????(0~3)
//LCD_DIR                       //??????(0~3)


//???????,??????????
//LCD_WR_CMD(cmd)               //??
//LCD_RD_DATA()                 //???

//8???????(?????16?)
//LCD_WR_8CMD(cmd)               //??
//LCD_WR_8DATA(data)            //???


//?????? ????? ???
#define LCD_EN_W        8
#define LCD_EN_H        16


/***************  LCD???  ***************/

void LCD_ST7735S_Conf(void);                                                                                    //LCD???

/***************  LCD??  ***************/

void LCD_ST7735S_point(Site_t site, u16 rgb565);                 //����
void LCD_ST7735S_rectangle(Site_t site, Size_t size, u16 rgb565);              //������
void LCD_ST7735S_char(Site_t site, u8 ascii, u16 Color, u16 bkColor);  //ASC�ַ�
void LCD_ST7735S_str(Site_t site, u8 *Str, u16 Color, u16 bkColor); //�ַ���

void LCD_num(Site_t site, u32 num, u16 Color, u16 bkColor);  //����
#define MAX_NUM_BIT 5                                                                                   //���ֵ����λ��
#define LCD_num_C(site,num,color,bkColor)           LCD_num_BC(site, num,MAX_NUM_BIT,color,bkColor)     //���֣�����������Ļ�������֣�
void LCD_num_BC(Site_t site, u32 num, u8 max_num_bit, u16 Color, u16 bkColor);  

void LCD_Img_gray(Site_t site, Size_t size, u8 *img);                   //���Ҷ�ͼ��
void LCD_Img_gray_Z(Site_t site, Size_t size, u8 *img, Size_t imgsize);  //���Ҷ�ͼ�񣨿����ţ�

#define BINARY_BGCOLOR  WHITE       //�����ֵ��ͼ�񱳾���ɫ
#define BINARY_COLOR    BLACK       //�����ֵ��ͼ��ǰ����ɫ
void LCD_Img_Binary(Site_t site, Size_t size, u8 *img);                  //����ֵ��ͼ��
void LCD_Img_Binary_Z(Site_t site, Size_t size, u8 *img, Size_t imgsize);  //����ֵ��ͼ�񣨿����ţ�
void LCD_wave(Site_t site,Size_t size,u8 *img,u8 maxval,u16 Color ,u16 bkColor);//������ʾ����������ɫ��maxval���ֵ��ʾ������ֵ�������������ֵ����
void LCD_wave_display(Site_t site,Size_t size,u8 *img,u8 maxval,u16 Color);       //������ʾ������������ɫ
void LCD_ST7735S_points          (Site_t *site,u32 point_num, u16 rgb565)    ;               //��һ�ѵ�









#endif


