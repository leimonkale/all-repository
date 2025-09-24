#include "servno.h"
#include <stm32f10x.h>

void motor_init(void)
{
	GPIO_InitTypeDef init;
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;
	
	//PA6 外部时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//PA7 引脚初始化
	init.GPIO_Pin = GPIO_Pin_6;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &init);
	
	
	//TIM3_CH2的外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*
		72000000(Hz) / (72) = 1000000(Hz) = 1000 次/ms
	*/
	
	//TIM3_CH1的基本初始化
	BaseInit.TIM_Prescaler = 72-1;	//预分频			定时器频率 f = 1MHZ  1次/us
	BaseInit.TIM_Period = 20000;	//记数器值			周期为 20ms   50Hz		20 * 1000 * 1 = 20000
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //二分频
	BaseInit.TIM_CounterMode = TIM_CounterMode_Up; //向上记数
	TIM_TimeBaseInit(TIM4, &BaseInit);
	
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;	//通道模式为 PWM1模式
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性：低电平
	OcInit.TIM_OutputState = ENABLE;			//输出状态：使能
	TIM_OC1Init(TIM4, &OcInit);					//初始化通道  CH1
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
void motor_start(void)
{
	TIM_Cmd(TIM4, ENABLE);
	TIM_SetCompare1(TIM4, 500); // 0度
}
void motor_stop(void)
{
	TIM_Cmd(TIM4, DISABLE);
}
void motor_set(int angle)
{
	int puls = 500 + angle * 2000 / 180;
	TIM_SetCompare1(TIM4, puls);
}
