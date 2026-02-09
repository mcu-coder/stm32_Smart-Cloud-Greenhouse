#include "ds18b20.h"

u16 DS18B20_750ms_Flag = 0;
u16 ds18b20_time = 0;

void DS18B20_Init(void)
{
	//开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = DS18B20;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS18B20_PROT, &GPIO_InitStructure);
	DS18B20_High;
}

void DS18B20_Write_Out_Input(u8 cmd)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(cmd)	//1 Out  0 Input
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = DS18B20;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(DS18B20_PROT, &GPIO_InitStructure);
	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = DS18B20;
		GPIO_Init(DS18B20_PROT, &GPIO_InitStructure);		
	}
}

u8 DS18B20_Write_Reset(void)
{
	u8 dat;
	
	DS18B20_Write_Out_Input(1);
	DS18B20_Low;
	Delay_us(480);	//480us
	DS18B20_High;
	Delay_us(60);	//60us
	DS18B20_Write_Out_Input(0);
	dat = GPIO_ReadInputDataBit(DS18B20_PROT,DS18B20);	//0为应答 1为不应答
	Delay_us(420); // 420us
	
	return dat;
}

void DS18B20_Write_Byte(u8 cmd)
{
	
	for(u8 i=0;i<8;i++)
	{
		DS18B20_Write_Out_Input(1);
		DS18B20_Low;
		Delay_us(2); //2us
		if(cmd & 0x01) DS18B20_High;
		else DS18B20_Low;
		Delay_us(60); //60us
		DS18B20_High;
		
		cmd >>= 1;
	}
}

u8 DS18B20_Read_Byte(void)
{
	
	u8 dat = 0;
	
	for(u8 i=0;i<8;i++)
	{
		
		dat >>= 1;
		
		DS18B20_Write_Out_Input(1);
		DS18B20_Low;
		Delay_us(2); //2us
		DS18B20_High;
		DS18B20_Write_Out_Input(0);
		if(GPIO_ReadInputDataBit(DS18B20_PROT,DS18B20) == SET)
		{
			dat |= 0x80; 
		}
		Delay_us(60); //60us
	}
	return dat;
}

void DS18B20_Read_Temp(float *temp)
{
	
	u8 MSB=0,MSL=0; u16 Temp=0;
	
	if(DS18B20_Write_Reset() == RESET)
	{
		
		DS18B20_Write_Reset();
		DS18B20_Write_Byte(0XCC);
		DS18B20_Write_Byte(0X44);
		
		DS18B20_750ms_Flag = 1;	//延迟750ms
		if(ds18b20_time > 750)
		{
			DS18B20_750ms_Flag = 0;
			ds18b20_time = 0;
			DS18B20_Write_Reset();
			DS18B20_Write_Byte(0XCC);
			DS18B20_Write_Byte(0XBE);
			
			MSL = DS18B20_Read_Byte();
			MSB = DS18B20_Read_Byte();
			Temp = MSB;
			Temp = Temp << 8|MSL;
			
			if((Temp & 0XF800) == 0XF800)	// 1111 1000 0000 0000
			{ 
				*temp =(((~Temp) + 0X01) * -0.0625);
			}
			else
			{
				*temp = Temp * 0.0625;
			}		
		}
	}
}



