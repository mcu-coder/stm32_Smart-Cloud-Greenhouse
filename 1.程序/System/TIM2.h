#ifndef __TIM2_H__
#define __TIM2_H__

#include "stm32f10x.h"                  // Device header
#include "key.h"   
#include "ds18b20.h"
#include "oled.h"
#include "relay.h"
#include "sensormodules.h"
#include "buzzer.h"
#include "led.h"
#include "gizwits_product.h"

void Timer2_Init(u16 Prescaler, u16 Period);

extern uint8_t mode;
extern uint8_t menu;
extern uint8_t OLED_Clear_Flag;

#endif
