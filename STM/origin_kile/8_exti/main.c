#include <stm32f10x.h>
#include "beep.h"

void gpio_init()
{
    // PB11 输入产生中断信号， PB0输出高电平
    GPIO_InitTypeDef init;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    init.GPIO_Pin = GPIO_Pin_0;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &init);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);    // 设置输出高电平

    init.GPIO_Pin = GPIO_Pin_11;
    init.GPIO_Mode = GPIO_Mode_IPU;     // 设置上拉输入
    GPIO_Init(GPIOB, &init);

    // 设置管脚 B11为外部中断线路
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
}

void exti_init()
{
    EXTI_InitTypeDef init;

    init.EXTI_Line = EXTI_Line11;                     // 中断线路，与 GPIO_PinSource11对应
    init.EXTI_Mode = EXTI_Mode_Interrupt;             // 中断模式
    init.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  // 中断触发方式：双边沿
    init.EXTI_LineCmd = ENABLE;                       // 使能外部中断
    EXTI_Init(&init);
}

void nvic_init()
{
    NVIC_InitTypeDef init;

    init.NVIC_IRQChannel = EXTI15_10_IRQn;
    init.NVIC_IRQChannelPreemptionPriority = 0;
    init.NVIC_IRQChannelSubPriority = 0;
    init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&init);
}

void EXTI15_10_IRQHandler()
{
    static int i = 1;
    if(i) 
    {
        beep_on();
    } 
    else 
    {
        beep_off();
    }
    i = ~i;

    // 清除外部中断标志
    EXTI_ClearITPendingBit(EXTI_Line11);
}

void delay(int ms)
{
    int i, j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 8090; j++);
    }
}

int main()
{
    beep_init();
    gpio_init();
    exti_init();
    nvic_init();
    
    delay(1000);
    beep_off();

    while(1)
    {
        beep_off();
    }
}
