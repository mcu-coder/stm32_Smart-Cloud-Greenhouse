#include "tim2.h"                  // Device header

static uint8_t motor_Flag_lock = 0;

void Timer2_Init(u16 Prescaler, u16 Period)	//0-65535
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)	//2ms定时中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) 
	{
		
		Key_scan();	//按键扫描函数
		
		if (DS18B20_750ms_Flag)
		{
			ds18b20_time += 2;
		}

		if (((KeyNum == 1) && (menu == 1)) || ((KeyNum == 1) && (menu == 2)))
		{
			KeyNum = 0;
			OLED_Clear_Flag = 1;
			menu = 3;
		}
		
		if (mode)
		{
			if ((sensorData.temp > Sensorthreshold.tempValue) || (sensorData.humi > Sensorthreshold.humiValue))
			{
				Relay_ON(1);
			}
			else
			{
				Relay_OFF(1);
			}
			
			if ((sensorData.soilTemp > Sensorthreshold.soilTempValue) || (sensorData.soilHumi < Sensorthreshold.soilHumiValue))
			{
				Relay_ON(0);
			}
			else
			{
				Relay_OFF(0);
			}
			
			if (sensorData.lux < Sensorthreshold.luxValue)
			{
				LED_ON();
			}
			else
			{
				LED_OFF();
			}
			
			if ((sensorData.CO2 > Sensorthreshold.CO2Value) && (motor_Flag_lock == 0))
			{
				motorFlag = 1;
				motor_Flag_lock = 1;
			}
			else if ((sensorData.CO2 < Sensorthreshold.CO2Value) && (motor_Flag_lock == 1))
			{
				motorFlag = 2;
				motor_Flag_lock = 0;
			}
			
			if ((mode == 1) && (sensorData.temp > Sensorthreshold.tempValue || sensorData.humi > Sensorthreshold.humiValue 
				|| sensorData.soilTemp > Sensorthreshold.soilTempValue || sensorData.soilHumi < Sensorthreshold.soilHumiValue
				|| sensorData.CO2 > Sensorthreshold.CO2Value))
			{
				Buzzer_ON();
			}
			else
			{
				Buzzer_OFF();
			}
		}
		
		//机智云配网按键，可以重新进行配网。	
		if((KeyNum == 44 && (menu == 1)) || (KeyNum == 44 && (menu == 2))) 
		{
			KeyNum = 0;
			gizwitsSetMode(2);
			Buzzer_ON();
			Delay_ms(300);
			Buzzer_OFF();
		}		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				
	}	
}

