#ifndef __TIM3_H_
#define __TIM3_H_

#include "stm32f10x.h"


static void GENERAL_TIM_NVIC_Config(void);
static void GENERAL_TIM_Mode_Config(void);
void GENERAL_TIM_Init(void);
void TIM3_IRQHandler(void);


#endif
