#include "stm32f10x.h"      //�Ҽ�������Կ���ѡ��            // Device header
#include "led.h"
// 50MHz ��Ƶ�µĴ�����ʱ

void led_init(void){
	GPIO_InitTypeDef init;
	//1���ܽŵ�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//�ܽŵĳ�ʼ��
	init.GPIO_Pin = GPIO_Pin_13 ;   //��д�ܽ�
	init.GPIO_Speed = GPIO_Speed_50MHz;   //��д����
	init.GPIO_Mode = GPIO_Mode_Out_PP;    //���ù���ģʽ
	GPIO_Init(GPIOC,&init); 
	
	init.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_0;   //��д�ܽ�
	init.GPIO_Speed = GPIO_Speed_50MHz;   //��д����
	init.GPIO_Mode = GPIO_Mode_Out_PP;    //���ù���ģʽ
	GPIO_Init(GPIOA,&init); 
	}
	
