#ifndef	__LED_H
#define	__LED_H

#include "stm32f10x.h"                  // Device header

#define LED				GPIO_Pin_5
#define LED_PROT		GPIOB

#define LED_HIGH		GPIO_SetBits(LED_PROT, LED)	
#define LED_LOW			GPIO_ResetBits(LED_PROT, LED)

void LED_Init(void);
void LED_ON(void);
void LED_OFF(void);
	

#endif
