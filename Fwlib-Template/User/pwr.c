#if 0

//�ùٷ��⺯�����ɣ���˴�ֻ�о��˲��ֳ���PWR�ٷ��⺯��

//�ȿ�ʱ�ӣ�RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); 

//(1)����PVD��⹦����ֵ�ȼ�:void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)


//(2)����˯��ģʽ: �����������жϻ��ѣ�
//			__WFI();__WFE();



//(3)����ֹͣģʽ:�����������жϻ��ѣ�/*��ֹͣģʽ�±����Ѻ�ʹ�õ���HSIʱ�ӣ��˴�����HSEʱ��*/PLLCLKSYSCLKConfig_STOP();��
//			void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
//      ���Ѻ�����ʱ��
	
//��	
//				��������������������ȡ��ǰʱ��״̬
//				//ʱ��Դ
//				clock_source_wakeup = RCC_GetSYSCLKSource ();
//				//ʱ��Ƶ��
//				RCC_GetClocksFreq(&clock_status_wakeup);
// ��


//(4)�������ģʽ:������WKUP����A0�����ػ��ѣ�
//			/*���WU״̬λ*/
//			PWR_ClearFlag (PWR_FLAG_WU);
//			
//			/* ʹ��WKUP���ŵĻ��ѹ��� ��ʹ��PA0*/
//			PWR_WakeUpPinCmd (ENABLE);
//			
//			/* �������ģʽ */
//			PWR_EnterSTANDBYMode();









#endif

