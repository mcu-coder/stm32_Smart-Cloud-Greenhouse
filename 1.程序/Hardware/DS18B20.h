#ifndef	__DS18B20_H
#define	__DS18B20_H

#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "tim2.h"

#define DS18B20 		GPIO_Pin_4
#define DS18B20_PROT 	GPIOA

#define DS18B20_High 	GPIO_SetBits(DS18B20_PROT,DS18B20)
#define DS18B20_Low 	GPIO_ResetBits(DS18B20_PROT,DS18B20)

extern u16 DS18B20_750ms_Flag;
extern u16 ds18b20_time;

void DS18B20_Init(void);
void DS18B20_Read_Temp(float *temp);
#endif
