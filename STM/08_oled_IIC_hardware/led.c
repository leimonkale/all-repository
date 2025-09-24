#include "stm32f10x.h"                  // Device header
#include "led.h"


//led  PC13  �͵�ƽ����

void led_init(void)
{
	//��������ŵ�ǰ��һ��
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//RCCʱ��ʹ�� �ϵ� ʹ��GPIOA����ʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
    //GPIO ��������ģʽ->ͨ���������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  //ѡ������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //ѡ������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��ģʽ ͨ���������
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    //GPIO �����������״̬ �ߵ�ƽ/�͵�ƽ
	//�õƲ���  PB15����ߵ�ƽ
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

