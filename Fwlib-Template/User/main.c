#include "stm32f10x.h"
#include "include.h"


int main()
{	
	//voltage = (dat16 / 65536.0) * 5.0;
	uint16_t voltage =  0x8000;
	
	//��ʼ��GPIO
	AD5667_Init();
	
	//����DAC
	AD5667_WRITE_REG(COMMAND, voltage);
	
	//��ѭ��
	while(1);
}


