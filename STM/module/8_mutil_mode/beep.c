#include "beep.h"
#include <stm32f10x.h>


void beep_init(void)
{
	GPIO_InitTypeDef init;
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;
	
	//PA6 �ⲿʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//PA6 ���ų�ʼ��
	init.GPIO_Pin = GPIO_Pin_6;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &init);
	
	
	
	//TIM3_CH1���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*
		72000000(Hz) / (72) = 1000000(Hz)
	*/
	
	//TIM3_CH1�Ļ�����ʼ��
	BaseInit.TIM_Prescaler = 72 - 1;	//Ԥ��Ƶ				f: 1MHz
	BaseInit.TIM_Period = 1000;		//������ֵ				�������� 1ms  1000Hz
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //����Ƶ
	BaseInit.TIM_CounterMode = TIM_CounterMode_Down; //���¼���
	TIM_TimeBaseInit(TIM3, &BaseInit);
	
	
	OcInit.TIM_Pulse = 200;					//�ȽϼĴ���ֵ��ռ�ձ�
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;	//ͨ��ģʽΪ PWM1ģʽ
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High;//������ԣ��ߵ�ƽ
	OcInit.TIM_OutputState = ENABLE;			//���״̬��ʹ��
	TIM_OC1Init(TIM3, &OcInit);					//��ʼ��ͨ��  CH1
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
