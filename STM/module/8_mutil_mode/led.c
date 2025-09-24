#include "led.h"
#include <stm32f10x.h>

void led_init()
{
	GPIO_InitTypeDef init;
	
	//1、管脚的时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//2、管脚初始化  pc13
	init.GPIO_Pin = GPIO_Pin_13;		//填写管脚
	init.GPIO_Speed = GPIO_Speed_50MHz;	//填写速率
	init.GPIO_Mode = GPIO_Mode_Out_PP;	//填写管脚工作模式
	GPIO_Init(GPIOC, &init); 
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void led_on()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}
void led_off()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
