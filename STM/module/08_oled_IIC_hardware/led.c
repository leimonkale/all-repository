#include "stm32f10x.h"                  // Device header
#include "led.h"


//led  PC13  低电平灯亮

void led_init(void)
{
	//变量定义放到前面一起
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//RCC时钟使能 上电 使能GPIOA外设时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
    //GPIO 配置引脚模式->通用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  //选择引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //选择速率
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择模式 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    //GPIO 配置引脚输出状态 高电平/低电平
	//让灯不亮  PB15输出高电平
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	
}

void led_on(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void led_off(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}

