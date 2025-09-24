#include "servno.h"
#include <stm32f10x.h>

void motor_init(void)
{
	GPIO_InitTypeDef init;
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;
	
	//PA6 �ⲿʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//PA7 ���ų�ʼ��
	init.GPIO_Pin = GPIO_Pin_6;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &init);
	
	
	//TIM3_CH2���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*
		72000000(Hz) / (72) = 1000000(Hz) = 1000 ��/ms
	*/
	
	//TIM3_CH1�Ļ�����ʼ��
	BaseInit.TIM_Prescaler = 72-1;	//Ԥ��Ƶ			��ʱ��Ƶ�� f = 1MHZ  1��/us
	BaseInit.TIM_Period = 20000;	//������ֵ			����Ϊ 20ms   50Hz		20 * 1000 * 1 = 20000
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //����Ƶ
	BaseInit.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM4, &BaseInit);
	
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;	//ͨ��ģʽΪ PWM1ģʽ
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High;//������ԣ��͵�ƽ
	OcInit.TIM_OutputState = ENABLE;			//���״̬��ʹ��
	TIM_OC1Init(TIM4, &OcInit);					//��ʼ��ͨ��  CH1
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
void motor_start(void)
{
	TIM_Cmd(TIM4, ENABLE);
	TIM_SetCompare1(TIM4, 500); // 0��
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
