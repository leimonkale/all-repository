#include <stm32f10x.h>


void gpio_init()
{
	GPIO_InitTypeDef init;
	
	//PA6 �ⲿʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//PA7 ���ų�ʼ��
	init.GPIO_Pin = GPIO_Pin_7;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &init);
}

void tim3_init()
{
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;
	
	//TIM3_CH2���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*
		72000000(Hz) / (72) = 1000000(Hz) = 1000 ��/ms
	*/
	
	//TIM3_CH1�Ļ�����ʼ��
	BaseInit.TIM_Prescaler = 72-1;	//Ԥ��Ƶ			��ʱ��Ƶ�� f = 1MHZ  1��/us
	BaseInit.TIM_Period = 20000;	//������ֵ			����Ϊ 20ms   50Hz		20 * 1000 * 1 = 20000
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //����Ƶ
	BaseInit.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3, &BaseInit);
	
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;	//ͨ��ģʽΪ PWM1ģʽ
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High;//������ԣ��͵�ƽ
	OcInit.TIM_OutputState = ENABLE;			//���״̬��ʹ��
	TIM_OC2Init(TIM3, &OcInit);					//��ʼ��ͨ��  CH1
	
	// TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
}
void delay(int ms)
{
	for(; ms != 0; ms--);
}
int main()
{
	gpio_init();
	tim3_init();
	while(1){
		TIM_SetCompare2(TIM3, 500); // 0��
		delay(1000);
		TIM_SetCompare2(TIM3, 1000); // 45��
		delay(1000);
		TIM_SetCompare2(TIM3, 1500); // 90��
		delay(1000);
		TIM_SetCompare2(TIM3, 2000); // 135��
		delay(1000);
		TIM_SetCompare2(TIM3, 2500); // 180��
		delay(1000);
	}
}
