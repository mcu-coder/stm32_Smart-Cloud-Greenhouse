#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"                  // Device header
#include "delay.h"

#define MOTOR_A GPIO_Pin_11
#define MOTOR_B GPIO_Pin_12
#define MOTOR_D GPIO_Pin_15
#define MOTOR1_PROT GPIOA

#define MOTOR_C GPIO_Pin_3
#define MOTOR2_PROT GPIOB

#define MOTOR_A_HIGH GPIO_SetBits(MOTOR1_PROT,MOTOR_A)
#define MOTOR_A_LOW GPIO_ResetBits(MOTOR1_PROT,MOTOR_A)

#define MOTOR_B_HIGH GPIO_SetBits(MOTOR1_PROT,MOTOR_B)
#define MOTOR_B_LOW GPIO_ResetBits(MOTOR1_PROT,MOTOR_B)

#define MOTOR_C_HIGH GPIO_SetBits(MOTOR2_PROT,MOTOR_C)
#define MOTOR_C_LOW GPIO_ResetBits(MOTOR2_PROT,MOTOR_C)

#define MOTOR_D_HIGH GPIO_SetBits(MOTOR1_PROT,MOTOR_D)
#define MOTOR_D_LOW GPIO_ResetBits(MOTOR1_PROT,MOTOR_D)

extern u8 FLAG; 
void MOTOR_Init(void);
void MOTOR_Rhythm_4_1_4(u8 step,u8 dly);
void MOTOR_Direction(u8 dir,u8 num,u8 dly);
void MOTOR_Direction_Angle(u8 dir,u8 num,u16 angle,u8 dly);
void MOTOR_STOP(void);

#endif
