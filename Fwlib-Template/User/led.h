/*********188������ר��led����****************
**********���ߣ���˼Զ******************
**********�ο�������******************
****************************************/


#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"

/* ����LED���ӵ�GPIO�˿�, PC0~7 LED0~7*/

#define LED0_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED0_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED0_GPIO_PIN		    GPIO_Pin_0			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED1_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED1_GPIO_PIN		    GPIO_Pin_1			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED2_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED2_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED2_GPIO_PIN		    GPIO_Pin_2			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED3_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED3_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED3_GPIO_PIN		    GPIO_Pin_3			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED4_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED4_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED4_GPIO_PIN		    GPIO_Pin_4			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED5_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED5_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED5_GPIO_PIN		    GPIO_Pin_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED6_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED6_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED6_GPIO_PIN		    GPIO_Pin_6			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LED7_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LED7_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED7_GPIO_PIN		    GPIO_Pin_7			        /* ���ӵ�SCLʱ���ߵ�GPIO */



/*LED����*/
#define ON  0
#define OFF 1


/********�⺯������LED��API************/
#define LED0(a) if(a)\
					GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED1(a) if(a)\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED2(a) if(a)\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED3(a) if(a)\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED4(a) if(a)\
					GPIO_SetBits(LED4_GPIO_PORT,LED4_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED4_GPIO_PORT,LED4_GPIO_PIN)
#define LED5(a) if(a)\
					GPIO_SetBits(LED5_GPIO_PORT,LED5_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED5_GPIO_PORT,LED5_GPIO_PIN)
#define LED6(a) if(a)\
					GPIO_SetBits(LED6_GPIO_PORT,LED6_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED6_GPIO_PORT,LED6_GPIO_PIN)
#define LED7(a) if(a)\
					GPIO_SetBits(LED7_GPIO_PORT,LED7_GPIO_PIN);\
					else\
					GPIO_ResetBits(LED7_GPIO_PORT,LED7_GPIO_PIN)


/************************�Ĵ�������LED********************************/
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

#define LED_ALL_ON          (GPIOC->ODR &= ~(0xff))
#define LED_ALL_OFF         (GPIOC->ODR |= 0xff)
#define LED_ALL_TOGGLE      (GPIOC->ODR ^= 0xffff)

/*************************�Ĵ���API*********************************/
#define LED0_TOGGLE		 digitalToggle(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED0_OFF		   digitalHi(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED0_ON			   digitalLo(LED0_GPIO_PORT,LED0_GPIO_PIN)

#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2_TOGGLE		 digitalToggle(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_OFF		   digitalHi(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_ON			   digitalLo(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3_TOGGLE		 digitalToggle(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_OFF		   digitalHi(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_ON			   digitalLo(LED3_GPIO_PORT,LED3_GPIO_PIN)

#define LED4_TOGGLE		 digitalToggle(LED4_GPIO_PORT,LED4_GPIO_PIN)
#define LED4_OFF		   digitalHi(LED4_GPIO_PORT,LED4_GPIO_PIN)
#define LED4_ON			   digitalLo(LED4_GPIO_PORT,LED4_GPIO_PIN)

#define LED5_TOGGLE		 digitalToggle(LED5_GPIO_PORT,LED5_GPIO_PIN)
#define LED5_OFF		   digitalHi(LED5_GPIO_PORT,LED5_GPIO_PIN)
#define LED5_ON			   digitalLo(LED5_GPIO_PORT,LED5_GPIO_PIN)

#define LED6_TOGGLE		 digitalToggle(LED6_GPIO_PORT,LED6_GPIO_PIN)
#define LED6_OFF		   digitalHi(LED6_GPIO_PORT,LED6_GPIO_PIN)
#define LED6_ON			   digitalLo(LED6_GPIO_PORT,LED6_GPIO_PIN)

#define LED7_TOGGLE		 digitalToggle(LED7_GPIO_PORT,LED7_GPIO_PIN)
#define LED7_OFF		   digitalHi(LED7_GPIO_PORT,LED7_GPIO_PIN)
#define LED7_ON			   digitalLo(LED7_GPIO_PORT,LED7_GPIO_PIN)


/*****************LED��ʼ������***********************************************/
void LED_Conf(void); 
#define LED_Init  LED_Conf
void LEDx_Conf(uint8_t LEDx);
void LED_ALL_SET(uint8_t stateValue);
#define LED_SetState LED_ALL_SET
#endif

