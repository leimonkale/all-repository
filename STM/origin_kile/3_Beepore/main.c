#include "stm32f10x.h"

// �Զ���װ��ֵ���飨ARR��������������Ƶ�ʣ�
// ����72MHzʱ�ӣ�PSC=71������Ƶ��1MHz��
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

// ���鳤�ȣ���������Ԫ��������ͬ��
uint8_t note_count = sizeof(arr_array) / sizeof(arr_array[0]);


void gpio_init(){
	GPIO_InitTypeDef init;
	//PA6 �ⲿʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//PA6 ���ų�ʼ��
	init.GPIO_Pin = GPIO_Pin_6;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOA, &init);

}

void tim3_init(){
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;

	//TIM3_CH1���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//72000000(Hz) /(7200) = 10000(Hz)
	
	//TIM3_CH1�Ļ�����ʼ��
	BaseInit.TIM_Prescaler = 35;  //Ԥ��Ƶ
	BaseInit.TIM_Period = 3816;     //������ֵ
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //����Ƶ
	BaseInit.TIM_CounterMode = TIM_CounterMode_Down; //���¼���
	TIM_TimeBaseInit(TIM3, &BaseInit);

	OcInit.TIM_Pulse = 1908;							//�ȽϼĴ���ֵ��ռ�ձ�
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;      
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High; //ͨ��ģʽΪ PWM1ģʽ
	OcInit.TIM_OutputState = ENABLE;          //������ԣ��ߵ�ƽ
	TIM_OC1Init(TIM3, &OcInit);               //���״̬��ʹ��

	TIM_Cmd(TIM3, ENABLE);                    //��ʼ��ͨ��
                                          //ʹ�ܶ�ʱ��3����ʱ��ʼ������
}

void delay_us(uint32_t us) {
    uint32_t i;
    // У׼���ݣ�50MHz = 50 ������/��s����ѭ������Լ 10 �����ڣ���ϵ��ȡ 5����ʵ��΢����
    for (i = 0; i < us * 5; i++) {
        __NOP(); // �ղ�����������ʱ��
    }
}

void delay_ms(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms; i++) {
        delay_us(1000); // ����΢����ʱ��ʵ�ֺ��뼶
    }
}

int main(){

	gpio_init();
	tim3_init();
	while(1){
		int i;
		for(i = 0;i<sizeof(arr_array);i++){
			TIM_SetAutoreload(TIM3, arr_array[i]);
			TIM_SetCompare1(TIM3, arr_array[i]/2);
			delay_ms(delay_array[i]);
		}
		
	}

}
