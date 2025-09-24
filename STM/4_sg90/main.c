#include <stm32f10x.h>


void gpio_init()
{
	GPIO_InitTypeDef init;
	
	//PA6 外部时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//PA7 引脚初始化
	init.GPIO_Pin = GPIO_Pin_7;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &init);
}

void tim3_init()
{
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;
	
	//TIM3_CH2的外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*
		72000000(Hz) / (72) = 1000000(Hz) = 1000 次/ms
	*/
	
	//TIM3_CH1的基本初始化
	BaseInit.TIM_Prescaler = 72-1;	//预分频			定时器频率 f = 1MHZ  1次/us
	BaseInit.TIM_Period = 20000;	//记数器值			周期为 20ms   50Hz		20 * 1000 * 1 = 20000
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //二分频
	BaseInit.TIM_CounterMode = TIM_CounterMode_Up; //向上记数
	TIM_TimeBaseInit(TIM3, &BaseInit);
	
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;	//通道模式为 PWM1模式
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性：低电平
	OcInit.TIM_OutputState = ENABLE;			//输出状态：使能
	TIM_OC2Init(TIM3, &OcInit);					//初始化通道  CH1
	
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
		TIM_SetCompare2(TIM3, 500); // 0度
		delay(1000);
		TIM_SetCompare2(TIM3, 1000); // 45度
		delay(1000);
		TIM_SetCompare2(TIM3, 1500); // 90度
		delay(1000);
		TIM_SetCompare2(TIM3, 2000); // 135度
		delay(1000);
		TIM_SetCompare2(TIM3, 2500); // 180度
		delay(1000);
	}
}
