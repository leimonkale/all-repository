#include "beep.h"
#include <stm32f10x.h>


void beep_init(void)
{
	GPIO_InitTypeDef init;
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;
	
	//PA6 外部时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//PA6 引脚初始化
	init.GPIO_Pin = GPIO_Pin_6;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &init);
	
	
	
	//TIM3_CH1的外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*
		72000000(Hz) / (72) = 1000000(Hz)
	*/
	
	//TIM3_CH1的基本初始化
	BaseInit.TIM_Prescaler = 72 - 1;	//预分频				f: 1MHz
	BaseInit.TIM_Period = 1000;		//记数器值				记数周期 1ms  1000Hz
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //二分频
	BaseInit.TIM_CounterMode = TIM_CounterMode_Down; //向下记数
	TIM_TimeBaseInit(TIM3, &BaseInit);
	
	
	OcInit.TIM_Pulse = 200;					//比较寄存器值，占空比
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;	//通道模式为 PWM1模式
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性：高电平
	OcInit.TIM_OutputState = ENABLE;			//输出状态：使能
	TIM_OC1Init(TIM3, &OcInit);					//初始化通道  CH1
	TIM_Cmd(TIM3, DISABLE);
}
void beep_on(void)
{
	TIM_Cmd(TIM3, ENABLE);
}
void beep_off(void)
{
	TIM_Cmd(TIM3, DISABLE);
}
