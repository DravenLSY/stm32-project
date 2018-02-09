#if 0
//������
#include "stm32f10x.h"
#include "include.h"


extern struct rtc_time systmtime;
extern struct rtc_time clocktime;

int main()
{	
	u32 timedata=0;
	Site_t site     = {0, 0};                          
	LCD_ST7735S_Conf();
  LCD_ST7735S_str(site,(u8*)"Calendar",FCOLOUR,BCOLOUR);
//  RTC_Conf();	   //RTC���ó�ʼ��	  �����ϵ�������ʱ���Ѵ���ע�͵��r����������ʼԪ�꣬������һ��
	RTC_CLOCK_Conf();  //ʱ���ʼ��
	
//	/*�������ӼĴ���*/
//	RTC_SetAlarm(Struct_To_UNIX(&clocktime)-TIME_ZOOM);
	
	while(1)
	{
		if(timebz==1)	   //ʱ�����ж�
		{
			timebz=0;	  //����
			timedata=RTC_GetCounter();//��ȡRTC��������ֵ
			Time_Calculate(timedata);//ʱ��ת������

			site.x=0;site.y=20;
			LCD_ST7735S_str(site,(u8*)"year:",FCOLOUR,BCOLOUR);
			site.x=40;site.y=20;
      LCD_num_BC(site,systmtime.tm_year,4,FCOLOUR,BCOLOUR);
			site.x=0;site.y=40;
			LCD_ST7735S_str(site,(u8*)"month:",FCOLOUR,BCOLOUR);
			site.x=48;site.y=40;
      LCD_num_BC(site,systmtime.tm_mon,4,FCOLOUR,BCOLOUR);
			site.x=0;site.y=60;
			LCD_ST7735S_str(site,(u8*)"day:",FCOLOUR,BCOLOUR);
			site.x=32;site.y=60;
      LCD_num_BC(site,systmtime.tm_mday,4,FCOLOUR,BCOLOUR);
			site.x=0;site.y=80;
      LCD_num_BC(site,systmtime.tm_hour,2,FCOLOUR,BCOLOUR);
			site.x=16;site.y=80;
			LCD_ST7735S_str(site,(u8*)":",FCOLOUR,BCOLOUR);
			site.x=24;site.y=80;
			LCD_num_BC(site,systmtime.tm_min,2,FCOLOUR,BCOLOUR);
			site.x=40;site.y=80;
			LCD_ST7735S_str(site,(u8*)":",FCOLOUR,BCOLOUR);
			site.x=48;site.y=80;
			LCD_num_BC(site,systmtime.tm_sec,2,FCOLOUR,BCOLOUR);
		}	
		if(timeclock==1)
		{
			//����ʱ�䵽
		}
	}			
}
#endif


#include "rtc.h"
#include "date.h"
#include "calendar.h"


/*ʱ��ṹ�壬Ĭ��ʱ��2000-01-01 00:00:00,������Ϊ��ʼԪ��*/
struct rtc_time systmtime=
{
0,8,20,3,9,2017,0
};

/*ʱ��ṹ�壬����ʱ��2000-01-01 00:00:08*/
struct rtc_time clocktime=
{
0,8,20,3,9,2017,0
};

//�洢ʱ����ַ���
uint8_t Lunar1[200],Lunar2[200],Term24[200];
// tm->tm_year, zodiac_sign[(tm->tm_year-3)%12], tm->tm_mon, tm->tm_mday, WEEK_STR[tm->tm_wday], tm->tm_hour, tm->tm_min, tm->tm_sec;
//UNIXʱ��� = %d ��ǰʱ��Ϊ: %d��(%s��) %d�� %d�� (����%s)  %0.2d:%0.2d:%0.2d\r


/* ���жϱ�־���������ж�ʱ��1����ʱ�䱻ˢ��֮����0 */
u8 timebz = 0;

/*���������־�����ж��������¼���1*/
u8 timeclock = 0;

/*���ڣ���Ф������ASCII��*/
char const *WEEK_STR[] = {"��", "һ", "��", "��", "��", "��", "��"};
char const *zodiac_sign[] = {"��", "��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��"};

/*Ӣ�ģ����ڣ���Ф������ASCII��*/
char const *en_WEEK_STR[] = { "Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char const *en_zodiac_sign[] = {"Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog"};



/*******************************************************************************
* �� �� ��         : rtc_init
* ��������		   : RTCʱ�ӡ��жϳ�ʼ��	//�������Ԫ��ʱ�䣬���ô˺���������RTC_CLOCK_Conf��������������ʱ�����ô˺���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void RTC_Conf()
{
   
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//�򿪵�Դʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);//�򿪴洢��ʱ��

	PWR_BackupAccessCmd(ENABLE);//ʹ�ܻ���ʧ��RTC�ͺ󱸼Ĵ�������
	BKP_DeInit();//������BKP��ȫ���Ĵ�������Ϊȱʡֵ
	RCC_LSEConfig(RCC_LSE_ON);//�����ⲿ���پ���LSE��
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET);//���ָ����RCC��־λ�������
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//����RTCʱ�ӣ�RTCCLK��
	RCC_RTCCLKCmd(ENABLE);//ʹ�ܻ���ʧ��RTCʱ��
	RTC_WaitForSynchro(); //�ȴ�RTC�Ĵ���ͬ��
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	RTC_ITConfig(RTC_IT_SEC,ENABLE);//ʹ�ܻ���ʧ��ָ����RTC�ж�
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	RTC_SetPrescaler(32767);//����Ԥ��Ƶ ʹ���ⲿ����Ϊ32.768K��Ҫ��1s�ж���Ԥ��Ƶ������Ϊ32767��ϵͳ���ڴ����ֻ����ϼ�1
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������	
		
}

void RTC_CLOCK_Conf()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);//�򿪺󱸱�������ʱ�Ӻ͵�Դʱ��
	PWR_BackupAccessCmd(ENABLE); //ʹ��RTC�ͺ�����Ĵ�������
	if(BKP_ReadBackupRegister(BKP_DR1)!=0XA5A5)//��ָ���ĺ󱸼Ĵ����ж�������
	{
		//��һ������  ��ʼ������
		//RTC��ʼ��
		RTC_Conf();
		RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_SetCounter(Struct_To_UNIX(&systmtime)-TIME_ZOOM);//����RTC��������ֵ 11:20��50
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	}
	else
	{	
		RTC_WaitForSynchro();//�ȴ�RTC�Ĵ���ͬ��	
		RTC_WaitForLastTask();//�ȴ�дRTC�Ĵ������		
	  RTC_ITConfig(RTC_IT_SEC,ENABLE);//ʹ��RTC���ж�    
		RTC_WaitForLastTask();//�ȴ�дRTC�Ĵ������	
	}
	NVIC_EnableIRQ(RTC_IRQn);
	RCC_ClearFlag();//�����λ��־��		
}

/*
 * ��������Time_Display
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ��-TimeVar RTC����ֵ����λΪ s
 * ���  ����
 * ����  ���ڲ�����
 */	
void Time_Calculate(uint32_t TimeVar)
{
	   static uint32_t FirstCalculate = 1;
	   uint32_t BJ_TimeVar;	

	   /*  �ѱ�׼ʱ��ת��Ϊ����ʱ��*/
	   BJ_TimeVar =TimeVar + TIME_ZOOM;

	   UNIX_To_Struct(BJ_TimeVar, &systmtime);/*�Ѷ�ʱ����ֵת��Ϊ����ʱ��*/	
	
	  if((!systmtime.tm_hour && !systmtime.tm_min && !systmtime.tm_sec)  || (FirstCalculate))
	  {
	      
	      GetChinaCalendar((u16)systmtime.tm_year, (u8)systmtime.tm_mon, (u8)systmtime.tm_mday, Lunar1);	//��ũ��ת��(ֻ����1901-2099��)
//					printf("\r\n ����������%0.2d%0.2d,%0.2d,%0.2d", Lunar1[0], Lunar1[1], Lunar1[2],  Lunar1[3]);
	
	      GetChinaCalendarStr((u16)systmtime.tm_year,(u8)systmtime.tm_mon,(u8)systmtime.tm_mday,Lunar2);//���빫�����ڵõ�ũ���ַ���, ��:GetChinaCalendarStr(2007,02,06,str) ����str="����������ʮ��"
//					printf("\r\n ����ũ����%s\r\n", Lunar2);
	
	     if(GetJieQiStr((u16)systmtime.tm_year, (u8)systmtime.tm_mon, (u8)systmtime.tm_mday, Term24))//���빫�����ڵõ�����24��������
//					printf("\r\n ����ũ����%s\r\n", Term24);
	
	      FirstCalculate = 0;
	  }	 	  	

	  /* ���ʱ���������ʱ�� */
//	  printf(" UNIXʱ��� = %d ��ǰʱ��Ϊ: %d��(%s��) %d�� %d�� (����%s)  %0.2d:%0.2d:%0.2d\r",TimeVar,
//	                    tm->tm_year, zodiac_sign[(tm->tm_year-3)%12], tm->tm_mon, tm->tm_mday, 
//	                    WEEK_STR[tm->tm_wday], tm->tm_hour, 
//	                    tm->tm_min, tm->tm_sec);
		
}

