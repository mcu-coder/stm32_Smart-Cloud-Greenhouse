#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "usart.h"

extern uint8_t Usart3_RxPacket[6];				//定义接收数据包数组
extern uint8_t Usart3_RxFlag;

void Uart3_Init(void);
uint8_t Usart3_GetRxFlag(void);
#endif


