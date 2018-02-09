#include "dht11.h"
#include "systick.h"

/*
int main()
{
	u8 DATA[5]={0};
	u8 T[3]={0};
	u8 DH[3]={0};
	TFT_Conf();
	TFT_ClearScreen(BLACK);	 //����
	while(1)
	{
		DHT_Start(DATA);
		
		T[0] = DATA[2]+'0';
		T[1] = '.';
		T[2] = DATA[3]+'0';
		DH[0] = DATA[0]+'0';
		DH[1] = '.';
		DH[2] = DATA[1]+'0';
		TFT_ClearScreen(BLACK);	 //����
		//GUI_Show12ASCII(10,90,(u8*)"DH : ",YELLOW,BLACK);
		//GUI_Show12ASCII(50,90,DH,YELLOW,BLACK);
		//GUI_Show12ASCII(10,110,(u8*)"T : ",YELLOW,BLACK);
		//GUI_Show12ASCII(50,110,T,YELLOW,BLACK);
	}
}
*/



static u32 U32FLAG=0;//�жϳ�ʱ

static u8 bit=0;//ÿһλ����
static u8 data=0;//ÿһ�ֽ�����



static void DHT_PP_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DHT_DATA_GPIO_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = DHT_DATA_GPIO_PIN;
	GPIO_Init(DHT_DATA_GPIO_PORT,&GPIO_InitStructure);
}

static void DHT_IPU_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = DHT_DATA_GPIO_PIN;
	GPIO_Init(DHT_DATA_GPIO_PORT,&GPIO_InitStructure);
}


static void ReadByte(void)
{
//	u8 str[1]="0";
	 u8 i;
   for(i=0;i<8;i++)	   
	 {	
	   	while(!DHT_DATA_READ);//�ȴ������ߣ�������ж�����λ
			delay_us(30);
			bit = 0;
			if(DHT_DATA_READ)
				bit = 1;
			U32FLAG = 0;
			while(DHT_DATA_READ)
			{
				U32FLAG++;
				if(U32FLAG==99999)
				{
						break;
				}
			}
			//GUI_Show12ASCII(10,50,(u8*)" Reading ",GREEN,BLACK);
			data<<=1;
	   	data|=bit;   
		}
//	 str[0] = data+'0';
	 //GUI_Show12ASCII(10,70,str,GREEN,BLACK);
}


void DHT_Start(u8* DATA)
{
	/*5�ֽ�40λ����*/
	u8 U8RH_data_H=0;
	u8 U8RH_data_L=0;
	u8 U8T_data_H=0;
	u8 U8T_data_L=0;
	u8 U8checkdata=0;

	DHT_PP_Conf();//���������ó��������
	
	DHT_DATA_LOW;//����18ms����ʼ�ź�
	delay_ms(18);
	DHT_DATA_HIGH;//������ʱ20-40us���ȴ���Ӧ
	//delay_us(40);
		
	DHT_IPU_Conf();//�����߹ܽ����ó���������	
	
	U32FLAG = 0;
	while(DHT_DATA_READ)//�ȴ�Ӧ�����������
	{
		U32FLAG++;
			if(U32FLAG==9999999)
			{
					//GUI_Show12ASCII(10,10,(u8*)"No Ack",RED,BLACK);
					while(1);
			}
	}
	//if(!DHT_VCC_READ)//��������ͣ����յ���Ӧ
	//{
		//GUI_Show12ASCII(10,10,(u8*)"   Ack   ",GREEN,BLACK);//��������ͣ����յ���Ӧ
		
		U32FLAG = 0;		
		while(!DHT_DATA_READ)//�ȴ��ӻ���������
		{
			U32FLAG++;
			if(U32FLAG==9999999)
			{
					//GUI_Show12ASCII(10,30,(u8*)"Init DOWN TimeOut",RED,BLACK);
					while(1);
			}
		}
		
		U32FLAG = 0;
		while(!DHT_DATA_READ)//�ȴ��ӻ��������ߣ���ʼ��������
		{
			U32FLAG++;
			if(U32FLAG==999999)
			{
					//GUI_Show12ASCII(10,30,(u8*)"Init UP TimeOut",RED,BLACK);
					while(1);
			}
		}
		
		//GUI_Show12ASCII(10,30,(u8*)"Init Ok ",GREEN,BLACK);
		
		//��ʼ����40bit����
		 ReadByte();
	   U8RH_data_H=data;
	   ReadByte();
	   U8RH_data_L=data;
	   ReadByte();
	   U8T_data_H=data;
	   ReadByte();
	   U8T_data_L=data;
	   ReadByte();
	   U8checkdata=data;
		
		//����ͨ��
		 DHT_DATA_HIGH;
		 //GUI_Show12ASCII(10,30,(u8*)"Read Ok",GREEN,BLACK);
		//����У�� 
	   bit = (U8T_data_H+U8T_data_L+U8RH_data_H+U8RH_data_L);
	   if(bit == U8checkdata)
	   {
	   	  *DATA=U8RH_data_H;
	   	  *(DATA+1)=U8RH_data_L;
		    *(DATA+2)=U8T_data_H;
	   	  *(DATA+3)=U8T_data_L;
	   	  *(DATA+4)=U8checkdata;
	   }
		 //GUI_Show12ASCII(10,70,(u8*)"Data Right",GREEN,BLACK);
	//}
	//else 
	//{
	//	//GUI_Show12ASCII(10,10,(u8*)"No Ack",RED,BLACK);
	//	while(1);
	//}
}

