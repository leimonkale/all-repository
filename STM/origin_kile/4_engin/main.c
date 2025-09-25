#include "stm32f10x.h" 

void gpio_init(){
    GPIO_InitTypeDef init;
    // PA6 ʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // ���ù���ʱ��ʹ�ܣ��ؼ���������������迪��AFIOʱ�ӣ�
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // PA6 ���ų�ʼ����TIM3_CH1��
    init.GPIO_Pin = GPIO_Pin_6;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    init.GPIO_Mode = GPIO_Mode_AF_PP;  // ���������������ȷ��
    GPIO_Init(GPIOA, &init);
}

void tim3_init(){
    TIM_TimeBaseInitTypeDef BaseInit;
    TIM_OCInitTypeDef OcInit;

    // TIM3 ʱ��ʹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // ��ʱ���������ã���Ϊ���ϼ�������ֱ�ۣ�
    BaseInit.TIM_Prescaler = 71;        // Ԥ��Ƶ��72MHz/(71+1)=1MHz��1��s/������
    BaseInit.TIM_Period = 19999;         // ���ڣ�2001��s��Լ500Hz��
    BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; // ����Ƶ
    BaseInit.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ������Ƽ���
    TIM_TimeBaseInit(TIM3, &BaseInit);

    // PWM����
    OcInit.TIM_Pulse = 1500;            // �Ƚ�ֵ��1000��s�ߵ�ƽ��ռ�ձ�~50%��
    OcInit.TIM_OCMode = TIM_OCMode_PWM1; // PWM1������ < CCR ʱ����ߵ�ƽ
    OcInit.TIM_OCPolarity = TIM_OCPolarity_High; // �ߵ�ƽ��Ч
    OcInit.TIM_OutputState = ENABLE;    // ʹ�����
    TIM_OC1Init(TIM3, &OcInit);

    // ʹ��Ԥװ�أ��ȶ�PWM�����
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_Cmd(TIM3, ENABLE);              // ������ʱ��
}

// У׼���΢����ʱ������72MHz��Ƶ��
void delay_us(uint32_t us) {
    uint32_t ticks = us * (72 / 8); // 72MHz��Ƶ�£�Լ8������=1��ѭ��
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
        TIM_SetCompare1(TIM3, 500);   // �ߵ�ƽ0.5ms�����ת0��
        delay_ms(600);/*
        TIM_SetCompare1(TIM3, 1500);  // �ߵ�ƽ1.5ms�����ת90��
        delay_ms(100);*/
        TIM_SetCompare1(TIM3, 2500);  // �ߵ�ƽ2.5ms�����ת180��
        delay_ms(600);
    }
}
