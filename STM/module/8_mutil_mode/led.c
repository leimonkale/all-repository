#include "led.h"
#include <stm32f10x.h>

void led_init()
{
	GPIO_InitTypeDef init;
	
	//1���ܽŵ�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//2���ܽų�ʼ��  pc13
	init.GPIO_Pin = GPIO_Pin_13;		//��д�ܽ�
	init.GPIO_Speed = GPIO_Speed_50MHz;	//��д����
	init.GPIO_Mode = GPIO_Mode_Out_PP;	//��д�ܽŹ���ģʽ
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
