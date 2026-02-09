#include "yl_69.h"

/**
  * @brief  YL69初始化程序
  * @param  
  * @retval 
  */
void YL69_Init(void)
{
	//开始GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//将YL69引脚设为模拟输入
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = YL69;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(YL69_PROT, &GPIO_InitStructure);
}

uint16_t YL69_ADC_Read(void)
{
	//设置指定ADC的规则组通道，采样时间
	return ADC_GetValue(ADC_Channel_1, ADC_SampleTime_55Cycles5);
}

uint16_t YL69_Average_Data(void)
{
	uint32_t  tempData = 0;
	for (uint8_t i = 0; i < YL69_READ_TIMES; i++)
	{
		tempData += YL69_ADC_Read();
		Delay_ms(5);
	}

	tempData /= YL69_READ_TIMES;
	return (uint16_t)tempData;
}

void YL69_PercentageData(uint8_t *Data)
{
	float voltage = 0;	
	voltage = YL69_Average_Data();
	*Data  = (1- (voltage / 4095)) * 100;
}
