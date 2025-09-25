#include "beep.h"
#include <stdint.h>
#include "stm32f10x.h"

// �Զ���װ��ֵ���飨ARR��������������Ƶ�ʣ�
// ����72MHzʱ�ӣ�PSC=35������Ƶ�� 72MHz / (35 + 1) = 2MHz ���������·������������ ���ɸ���ʵ�����У׼��
uint16_t arr_array[] = {
    512, 1024, 512, 2048, 512, 1024, 256, 1024,
    256, 512, 128, 512, 128, 256, 64, 256,
    512, 1024, 512, 2048, 512, 1024, 256, 1024,

    // ����2���������죨Լ5�룩
    128, 256, 64, 128, 64, 128, 32, 128,
    32, 64, 32, 128, 32, 64, 16, 64,
    16, 32, 8, 32, 8, 16, 4, 16,

    // ����3����Ƶ�����Լ5�룩
    4, 8, 4, 16, 8, 16, 16, 32,
    16, 32, 32, 64, 32, 64, 64, 128,
    64, 128, 128, 256, 128, 256, 256, 512,

    // ����4����Ƶ�𵴣�Լ5�룩
    256, 512, 256, 1024, 512, 1024, 1024, 2048,
    1024, 2048, 2048, 4096, 2048, 4096, 4096, 8192,
    4096, 8192, 8192, 4096, 8192, 4096, 2048, 4096,

    // ����5����Ƶ���ɣ�Լ5�룩
    2048, 1024, 2048, 1024, 512, 1024, 512, 256,
    512, 256, 128, 256, 128, 64, 128, 64,
    256, 128, 256, 128, 512, 256, 512, 1024,

    // ����6����βѭ����Լ5�룩
    512, 1024, 256, 512, 128, 256, 64, 128,
    32, 64, 16, 32, 8, 16, 4, 8,
    8, 16, 16, 32, 32, 64, 64, 128
};

// ��ʱ���飨��λ��ms��������ÿ�������Ĳ���ʱ��������������һһ��Ӧ
uint16_t delay_array[] = {
    // ��һ����ʱ���������ࣩ
    300, 300, 300, 400, 300, 300, 200, 400,
    200, 300, 150, 300, 150, 200, 100, 200,

    // �ڶ�����ʱ���Կ죩
    250, 250, 250, 350, 250, 250, 180, 350,
    180, 250, 130, 250, 130, 180, 90, 180,

    // ��������ʱ���ӿ죩
    100, 150, 100, 200, 100, 150, 80, 150,
    80, 100, 60, 100, 60, 80, 50, 80,

    // ���Ķ���ʱ���ټӿ죩
    50, 80, 50, 100, 80, 100, 100, 150,
    100, 150, 150, 200, 150, 200, 200, 300,

    // �������ʱ���Ż���
    200, 300, 200, 400, 300, 400, 400, 500,
    400, 500, 500, 600, 500, 600, 600, 700,

    // ��������ʱ��������β��
    500, 400, 500, 400, 300, 400, 300, 200,
    300, 200, 150, 200, 150, 100, 150, 100
};

// ��ʱ��������ʵ�֣��������׼��ʹ��ϵͳ�δ�ʱ���ȣ�
void delay_us(uint32_t us) {
    uint32_t i;
    // У׼���ݣ�����ʵ�� CPU Ƶ�ʵ���ѭ������������ֻ��ʾ������ʵ���Ż�
    for (i = 0; i < us * 10; i++) {
        __NOP(); 
    }
}

void delay_ms(uint32_t ms) {
	uint32_t i;
    for (i = 0; i < ms; i++) {
        delay_us(1000);
    }
}

// ���鳤�ȣ���������Ԫ��������ͬ��
uint8_t note_count = sizeof(arr_array) / sizeof(arr_array[0]);

// ���ڿ��Ʒ������������ص� GPIO ��ض��壨��ʹ���ⲿ�жϿ��ƻ�������ʱ�õ����ɰ���������ţ�
#define BEEP_CTRL_GPIO_PORT    GPIOB
#define BEEP_CTRL_GPIO_PIN     GPIO_Pin_0
#define BEEP_CTRL_RCC          RCC_APB2Periph_GPIOB

// ���� PWM ��������������Ķ�ʱ����ͨ����ض��壨������ TIM3_CH1 �������ɰ����޸ģ�
#define BEEP_TIM               TIM3
#define BEEP_TIM_CH            TIM_Channel_1
#define BEEP_TIM_RCC_APB1      RCC_APB1Periph_TIM3
#define BEEP_GPIO_PORT         GPIOA
#define BEEP_GPIO_PIN          GPIO_Pin_6
#define BEEP_GPIO_AF_RCC       RCC_APB2Periph_GPIOA

// ����ʵ��
void beep_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    TIM_TimeBaseInitTypeDef tim_base_init_struct;
    TIM_OCInitTypeDef tim_oc_init_struct;

    // ��ʼ�����Ʒ������������ص� GPIO���������������ͨ GPIO ���ƿ���ʱ��
    RCC_APB2PeriphClockCmd(BEEP_CTRL_RCC, ENABLE);
    gpio_init_struct.GPIO_Pin = BEEP_CTRL_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BEEP_CTRL_GPIO_PORT, &gpio_init_struct);
    GPIO_ResetBits(BEEP_CTRL_GPIO_PORT, BEEP_CTRL_GPIO_PIN);  // ��ʼ�ر�

    // ��ʼ�� PWM �����ص� GPIO �Ͷ�ʱ��
    RCC_APB2PeriphClockCmd(BEEP_GPIO_AF_RCC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(BEEP_TIM_RCC_APB1, ENABLE);

    // ���� PWM �������
    gpio_init_struct.GPIO_Pin = BEEP_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);

    // ���ö�ʱ��ʱ��
    tim_base_init_struct.TIM_Prescaler = 35;   // Ԥ��Ƶ���ɸ���ʵ���������
    tim_base_init_struct.TIM_Period = 3816;    // �Զ���װ��ֵ�����Ԥ��Ƶ����Ƶ��
    tim_base_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_base_init_struct.TIM_CounterMode = TIM_CounterMode_Down;  // ���¼���ģʽ
    TIM_TimeBaseInit(BEEP_TIM, &tim_base_init_struct);

    // ���� PWM ģʽ
    tim_oc_init_struct.TIM_OCMode = TIM_OCMode_PWM1;
    tim_oc_init_struct.TIM_OCPolarity = TIM_OCPolarity_High;
    tim_oc_init_struct.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_init_struct.TIM_Pulse = 1908;  // ��ʼ�Ƚ�ֵ������ռ�ձ�
    TIM_OC1Init(BEEP_TIM, &tim_oc_init_struct);  // �������ͨ���������� TIM_Channel_1 ���� TIM_OC1Init

    TIM_Cmd(BEEP_TIM, ENABLE);  // ʹ�ܶ�ʱ��
}

void beep_on(void)
{
    GPIO_SetBits(BEEP_CTRL_GPIO_PORT, BEEP_CTRL_GPIO_PIN);  // ��ͨ GPIO ���ƴ򿪣���������ַ�ʽ��
    // Ҳ����ͨ������ PWM ռ�ձȵȷ�ʽ�÷��������ض�Ƶ�ʳ����죬���磺
    // TIM_SetCompare1(BEEP_TIM, TIM_GetAutoreload(BEEP_TIM) / 2);  // ռ�ձ� 50% ʾ��
}

void beep_off(void)
{
    GPIO_ResetBits(BEEP_CTRL_GPIO_PORT, BEEP_CTRL_GPIO_PIN);  // ��ͨ GPIO ���ƹرգ���������ַ�ʽ��
    // ���߹ر� PWM �����
    // TIM_SetCompare1(BEEP_TIM, 0);  // ռ�ձ� 0��ֹͣ PWM ���
}

// �����Զ����������к���
void play_custom_tone(void)
{
	uint8_t i;
    for ( i = 0; i < note_count; i++) {
        TIM_SetAutoreload(BEEP_TIM, arr_array[i]);
        TIM_SetCompare1(BEEP_TIM, arr_array[i] / 2);  // ռ�ձ� 50% ʾ�����ɰ������
        delay_ms(delay_array[i]);
    }
}

