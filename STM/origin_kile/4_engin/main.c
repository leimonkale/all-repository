#include "stm32f10x.h" 

void gpio_init(){
    GPIO_InitTypeDef init;
    // PA6 时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 复用功能时钟使能（关键：复用推挽输出需开启AFIO时钟）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // PA6 引脚初始化（TIM3_CH1）
    init.GPIO_Pin = GPIO_Pin_6;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    init.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出（正确）
    GPIO_Init(GPIOA, &init);
}

void tim3_init(){
    TIM_TimeBaseInitTypeDef BaseInit;
    TIM_OCInitTypeDef OcInit;

    // TIM3 时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // 定时器基础配置（改为向上计数，更直观）
    BaseInit.TIM_Prescaler = 71;        // 预分频：72MHz/(71+1)=1MHz（1μs/计数）
    BaseInit.TIM_Period = 19999;         // 周期：2001μs（约500Hz）
    BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; // 不分频
    BaseInit.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数（推荐）
    TIM_TimeBaseInit(TIM3, &BaseInit);

    // PWM配置
    OcInit.TIM_Pulse = 1500;            // 比较值：1000μs高电平（占空比~50%）
    OcInit.TIM_OCMode = TIM_OCMode_PWM1; // PWM1：计数 < CCR 时输出高电平
    OcInit.TIM_OCPolarity = TIM_OCPolarity_High; // 高电平有效
    OcInit.TIM_OutputState = ENABLE;    // 使能输出
    TIM_OC1Init(TIM3, &OcInit);

    // 使能预装载（稳定PWM输出）
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_Cmd(TIM3, ENABLE);              // 启动定时器
}

// 校准后的微秒延时（基于72MHz主频）
void delay_us(uint32_t us) {
    uint32_t ticks = us * (72 / 8); // 72MHz主频下，约8个周期=1次循环
    while(ticks--);
}

void delay_ms(uint32_t ms) {
    while(ms--) delay_us(1000);
}

int main(){
    gpio_init();
    tim3_init();
	delay_ms(600)

    while(1){
        TIM_SetCompare1(TIM3, 500);   // 高电平0.5ms→舵机转0°
        delay_ms(600);/*
        TIM_SetCompare1(TIM3, 1500);  // 高电平1.5ms→舵机转90°
        delay_ms(100);*/
        TIM_SetCompare1(TIM3, 2500);  // 高电平2.5ms→舵机转180°
        delay_ms(600);
    }
}
