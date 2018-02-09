#if 0 
#include "stm32f10x.h"
#include "sd.h"
#include <math.h>
#include "ff.h"
#include "diskio.h"
#include "myfatapp.h"
#include "mp3player.h"
#include "gui.h"
#include "flash.h"
#include "key.h"
#include "timerx.h"
#include "led.h"

void GUI_DisplayInit(void);


//VS1003/1053 MP3ģ��������STM32��������߷�ʽ��
//5V---5V
//GND--GND
//XRST--PG8
//MISO--PA6
//MOSI--PA7
//SCLK--PA5
//DREQ--PG7
//XCS--PE6
//XDCS--PG6

//ʵ��ǰ�����SD������SD����Ŀ¼�·������ǹ����ڵ�SD���ļ������ļ�






/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

FileNameTypeDef filename[30];
int main(void)
{
	FATFS fs;
	uint32_t sdCapacity, free;
    uint8_t dat[9] = {"0:/MUSIC"}, i, j, k;  //Ҫ��ʾ��ͼƬ���ļ���ַ
    uint8_t misicFile[30];

    /* ��ʼ�� */
    TFT_Init();
	FLASH_Init();
	MP3_Init();
    KEY_Config();
    LED_Config();
    TIMER6_Config(1000);     //��ʱ10ms
//   GPIOC->ODR = GPIO_Pin_0;
    TFT_ClearScreen(BLACK);
	while(SD_Init())
	{
        GUI_Show12Char(0, 0, "SD card error!", RED, BLACK);
	}
		
	f_mount(0, &fs);
	while(FATFS_GetFree("0", &sdCapacity, &free) != 0)
    {
        GUI_Show12Char(0, 21, "FATfs error!", RED, BLACK);   
    }
    /* �������� */
    MP3_Volume = 230;
    MP3_AudioSetting(MP3_Volume);
    /* ��ʼ����ʾ */
	GUI_DisplayInit();

	/*  ɨ���ļ���ַ�������е��ļ� */
    FATFS_ScanFiles(dat, filename);
	
    while(1)	//ɨ��30���ļ�
	{
		/* �ж��Ƿ���PM3ͼƬ�ļ� */
		if((filename[i].type[1] == 'm') && (filename[i].type[2] == 'p') &&
           (filename[i].type[3] == '3')) 
		{
			/* �����ļ�·��,������ļ�·�� */
			k = 0;
			while(*(dat + k) != '\0')
			{
				*(misicFile + k) = *(dat + k);
				k++;
			}

            /* ·��֮�����һб�� */
			*(misicFile + k) = '/';
			k++;

            /* ����ļ��������� */
			j = 0;
			while(filename[i].name[j] != '\0')
			{
				*(misicFile + k) = filename[i].name[j];
				k++;
				j++;	
			}

            /* ����ļ���׺ */
			j = 0;
			while(filename[i].type[j] != '\0')
			{
				*(misicFile + k) = filename[i].type[j];
				k++;
				j++;	
			}

            /* �ļ�������һ���������� */
            *(misicFile + k) = '\0';

			/* ��ʾ���ŵĸ��������Ÿ��� */
            GUI_Box(0, 126, TFT_XMAX, 141, BLACK);    //�����ʾλ��
            GUI_Show12Char(0, 126, misicFile, RED, BLACK);        
            MP3_PlaySong(misicFile);
		}
		i++;
        if(i > 30)
        {
            i = 0;
        }
	}		
}

/****************************************************************************
* Function Name  : GUI_DisplayInit
* Description    : ��ʼ��������ʾ
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void GUI_DisplayInit(void)
{
    TFT_ClearScreen(BLACK);
    GUI_Show16Chinese(80, 0, "���пƼ�", RED, BLACK);
    GUI_Show12Char(90, 21, "PRECHIN", RED, BLACK);
    GUI_Show12Char(60, 42, "www.prechin.com", RED, BLACK);
    GUI_Show12Char(76, 63, "MP3������ʵ��", RED, BLACK);
    GUI_Show12Char(0, 84, "��������Ϊ��230", RED, BLACK);
    GUI_Show12Char(0, 105, "���ڲ��ŵĸ���Ϊ��", RED, BLACK);
    GUI_Show12Char(0, 147, "KEY_UP������+", BLUE, BLACK);
    GUI_Show12Char(0, 168, "KEY_WOWN������-", BLUE, BLACK);
    GUI_Show12Char(0, 189, "KEY_RIGHT����һ��", BLUE, BLACK);
}


#endif



#include "vs10xx.h"
#include "systick.h"
#include "spi.h"

/****************************************************************************
* Function Name  : VS10XX_DelayMs
* Description    : ��ʱ���뼶����.
* Input          : ms����ʱ��������
* Output         : None
* Return         : None
****************************************************************************/

#define VS10XX_DelayMs(x) {SYSTICK_Delay1ms(x);}

/****************************************************************************
* Function Name  : VS_Config
* Description    : ��VS10XXоƬʹ�õ�IO�ں�SPI���г�ʼ��.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void VS10XX_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOD, ENABLE);
	
	/* VS10XX_CS �� PE6 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure); //����Ǵ�����Ƭѡ��Ϊ�˷�ֹӰ��ѡ��ر�
    GPIO_SetBits(GPIOD, GPIO_Pin_6);

	/* VS10XX_RESET �� PG8,S10xx_XDCS �� PG6*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;
	
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	/* VS10XX_DREQ ��PG7 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	/* ��ʼ��SPI1 */
	SPI1_Conf();
}

/****************************************************************************
* Function Name  : VS10XX_WriteCmd
* Description    : VS10XXд��һ������.
* Input          : addr��д���ַ
*                * cmd��д������
* Output         : None
* Return         : 0��д��ɹ���0xFF��д��ʧ�ܡ�
****************************************************************************/

int8_t VS10XX_WriteCmd(uint8_t addr, uint16_t cmd)
{
	uint16_t i = 0;

	while(VS_DREQ == 0)	//�ȴ�����
	{
		i++;
		if(i > 0xAFFF)
		{
			return 0xFF;
		}
	}

	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);  //����SPI1����
	VS_XDCS_SET; 	 
	VS_XCS_CLR;

	SPI1_WriteReadData(VS_WRITE_COMMAND);      //����д����
	SPI1_WriteReadData(addr);				   //���͵�ַ
	SPI1_WriteReadData(cmd >> 8);	           //�ȷ���8λ
	SPI1_WriteReadData(cmd & 0x00FF);
	VS_XCS_SET;

	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);
	return 0;
}

/****************************************************************************
* Function Name  : VS10XX_ReadData
* Description    : VS10XX��ȡһ������.
* Input          : addr��Ҫ��ȡ�ĵ�ַ
* Output         : None
* Return         : ��ȡ����16λ����
****************************************************************************/

uint16_t VS10XX_ReadData(uint8_t addr)
{
	uint16_t readValue, i;

	while(VS_DREQ == 0)	//�ȴ�����
	{
		i++;
		if(i > 0xAFFF)
		{
			return 0xFFFF;
		}
	}

	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);  //����SPI1����
	VS_XDCS_SET; 	 
	VS_XCS_CLR;

	SPI1_WriteReadData(VS_READ_COMMAND);	   //���Ͷ�����
	SPI1_WriteReadData(addr);				   //���͵�ַ
	readValue = SPI1_WriteReadData(0xFF);	   //�ȶ���8λ
	readValue <<= 8;
	readValue |= SPI1_WriteReadData(0xFF);

	VS_XCS_SET;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);    //����SPI1�ٶ�

	return readValue;
}

/****************************************************************************
* Function Name  : VS_HardwareReset
* Description    : Ӳ����λVS10XX.
* Input          : None
* Output         : None
* Return         : 0���ɹ���0xFF��ʧ�ܡ�
****************************************************************************/
 
int8_t VS10XX_HardwareReset(void)
{
	uint16_t i = 0;

	VS_RST_CLR;
	VS10XX_DelayMs(20);
	VS_XDCS_SET;  //ȡ�����ݴ���
	VS_XCS_SET;   //ȡ�����ݴ���
	VS_RST_SET;

	while(VS_DREQ == 0)
	{
		i++;
		if(i > 0x0FFF)
		{
			return 0xFF;
		}	
	}
	VS10XX_DelayMs(20);
	
	return 0;
}

/****************************************************************************
* Function Name  : VS10XX_SoftReset
* Description    : �����λVS10xx��ͬʱ����ʱ�ӡ�
* Input          : None
* Output         : None
* Return         : 0���ɹ���0xFF��ʧ�ܡ�
****************************************************************************/

int8_t VS10XX_SoftReset(void)
{
	uint16_t i = 0;
	
	while(VS_DREQ == 0)
	{
		i++;
		if(i > 0x5FFF)
		{
			return 0xFF;
		}	
	}	
	SPI1_WriteReadData(0xFF);
	
	i = 0;
	while(VS10XX_ReadData(SCI_MODE) != 0x0800)	// �����λ,��ģʽ
	{
		VS10XX_WriteCmd(SCI_MODE, 0x0804);      // �����λ,��ģʽ	    
		VS10XX_DelayMs(2);                      //�ȴ�����1.35ms
		i++;
		if(i > 0x5FFF)
		{
			return 0xFF;
		}	
	}
	
	i = 0;
	while(VS_DREQ == 0)
	{
		i++;
		if(i > 0x5FFF)
		{
			return 0xFF;
		}	
	}

	i = 0;
	while(VS10XX_ReadData(SCI_CLOCKF) != 0X9800) //����VS10XX��ʱ��,3��Ƶ ,1.5xADD 
	{
		VS10XX_WriteCmd(SCI_CLOCKF, 0X9800);     //����VS10XX��ʱ��,3��Ƶ ,1.5xADD
		VS10XX_DelayMs(20);
		i++;
		if(i > 0x5FFF)
		{
			return 0xFF;
		} 	    
	}		    										    
	
	return 0;
}

/****************************************************************************
* Function Name  : VS10XX_RAM_Test
* Description    : ��оƬ�����ڴ���ԣ���ȡ��0x8000��ʾ������ɣ���ȡ��0x807F
*                * ��VS1003��ã���ȡ��0X83FF�Ǳ�ʾVS1053��á�
*                * ���Գ�ʼ������Ϊ��0x4D,0xEA,0x6D,0x54,0,0,0,0��
* Input          : None
* Output         : None
* Return         : 0xFFFF������ʧ�ܡ��򷵻ز���״̬
****************************************************************************/

uint16_t VS10XX_RAM_Test(void)
{
	uint16_t i = 0;

	VS10XX_HardwareReset();
	VS10XX_WriteCmd(SCI_MODE, 0x0820);	// Allow SCI tests 
	
	while(VS_DREQ == 0)
	{
		i++;
		if(i > 0x0FFF)
		{
			return 0xFFFF;
		}	
	}
	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);  //����SPI1����
	VS_XDCS_CLR;	       		    // xDCS = 1��ѡ��VS10XX�����ݽӿ�

	SPI1_WriteReadData(0x4D);
	SPI1_WriteReadData(0xEA);
	SPI1_WriteReadData(0x6D);
	SPI1_WriteReadData(0x54);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	
	VS10XX_DelayMs(150);
	VS_XDCS_SET;
	
	return VS10XX_ReadData(SCI_HDAT0); // VS1003�õ���ֵΪ0x807F;VS1053Ϊ0X83FF;			
}

/****************************************************************************
* Function Name  : VS10XX_SineTest
* Description    : ��оƬ�������Ҳ���.
*                * ������������Ϊ��0x53,0xEF,0x6E,n,0,0,0,0��
*                * �˳���������Ϊ��0x45,0x78,0x69,0x74,0,0,0,0
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void VS10XX_SineTest(void)
{
	uint16_t i;

	VS10XX_HardwareReset();
	VS10XX_WriteCmd(SCI_MODE,0x0820);    // Allow SCI tests
	
	while(VS_DREQ == 0)
	{
		i++;
		if(i > 0x5FFF)
		{
			return ;
		}	
	}
	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);  //����SPI1����

	VS_XDCS_CLR;	       		    // xDCS = 1��ѡ��VS10XX�����ݽӿ�
	SPI1_WriteReadData(0x53);	    //�������Ҳ���n = 0x24
	SPI1_WriteReadData(0xEF);
	SPI1_WriteReadData(0x6E);
	SPI1_WriteReadData(0x24);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	VS_XDCS_SET;

	VS10XX_DelayMs(100);

	VS_XDCS_CLR;			  // �˳����Ҳ���
	SPI1_WriteReadData(0x45);
	SPI1_WriteReadData(0x78);
	SPI1_WriteReadData(0x69);
	SPI1_WriteReadData(0x74);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	SPI1_WriteReadData(0x00);
	VS_XDCS_SET;

	VS10XX_DelayMs(100);
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);
}

/****************************************************************************
* Function Name  : VS10XX_SendMusicData
* Description    : ������������
* Input          : dat�����ݻ�����
* Output         : None
* Return         : 0�����ͳɹ���0xFF������æ��δ���ͳɹ�
****************************************************************************/

uint8_t VS10XX_SendMusicData(uint8_t *dat)
{
    uint8_t i;
    if(VS_DREQ != 0)
    {
        SPI1_SetSpeed(SPI_BaudRatePrescaler_8);
        VS_XDCS_CLR;
        for(i=0; i<32; i++)
        {
            SPI1_WriteReadData(dat[i]);
        }
        VS_XDCS_SET;
        return 0;
    }
    else
    {
        return 0xFF;
    }
}


