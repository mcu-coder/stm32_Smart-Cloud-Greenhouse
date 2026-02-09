#ifndef	__RELAY_H
#define	__RELAY_H

#include "stm32f10x.h"                  // Device header

#define Relay1		GPIO_Pin_12
#define Relay2		GPIO_Pin_13
#define Relay_PROT	GPIOB

void Relay_Init(void);
void Relay_ON(u8 num);
void Relay_OFF(u8 num);

#endif
