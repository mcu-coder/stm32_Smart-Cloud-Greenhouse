#ifndef _YL_69_H_
#define _YL_69_H_

#include "stm32f10x.h"                  // Device header
#include "adcx.h"
#include "Delay.h"

#define YL69				GPIO_Pin_1
#define YL69_PROT			GPIOA

#define YL69_READ_TIMES	10

void YL69_Init(void);
uint16_t YL69_ADC_Read(void);
uint16_t YL69_Average_Data(void);
void YL69_PercentageData(uint8_t *Data);

#endif
