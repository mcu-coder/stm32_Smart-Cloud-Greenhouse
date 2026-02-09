#include "relay.h"


void Relay_Init(void)
{
	//ø™∆ÙGPIOB ±÷”
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//≈‰÷√GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Relay1 | Relay2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Relay_PROT, &GPIO_InitStructure);
	
	GPIO_ResetBits(Relay_PROT, Relay1);
	GPIO_ResetBits(Relay_PROT, Relay2);
}

void Relay_ON(u8 num)
{
	if(num)
	{
		GPIO_SetBits(Relay_PROT, Relay1);
	}
	else
	{
		GPIO_SetBits(Relay_PROT, Relay2);
	}
}

void Relay_OFF(u8 num)
{
	if(num)
	{
		GPIO_ResetBits(Relay_PROT, Relay1);
	}
	else
	{
		GPIO_ResetBits(Relay_PROT, Relay2);
	}
}
