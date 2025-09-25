#include <stm32f10x.h>
#include "beep.h"

void gpio_init()
{
    // PB11 ��������ж��źţ� PB0����ߵ�ƽ
    GPIO_InitTypeDef init;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    init.GPIO_Pin = GPIO_Pin_0;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &init);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);    // ��������ߵ�ƽ

    init.GPIO_Pin = GPIO_Pin_11;
    init.GPIO_Mode = GPIO_Mode_IPU;     // ������������
    GPIO_Init(GPIOB, &init);

    // ���ùܽ� B11Ϊ�ⲿ�ж���·
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
}

void exti_init()
{
    EXTI_InitTypeDef init;

    init.EXTI_Line = EXTI_Line11;                     // �ж���·���� GPIO_PinSource11��Ӧ
    init.EXTI_Mode = EXTI_Mode_Interrupt;             // �ж�ģʽ
    init.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  // �жϴ�����ʽ��˫����
    init.EXTI_LineCmd = ENABLE;                       // ʹ���ⲿ�ж�
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

    // ����ⲿ�жϱ�־
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
