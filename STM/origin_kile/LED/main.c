#include "stm32f10x.h"      //�Ҽ�������Կ���ѡ��            // Device header

// 50MHz ��Ƶ�µĴ�����ʱ
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
	GPIO_InitTypeDef init;
	//1���ܽŵ�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//�ܽŵĳ�ʼ��
	init.GPIO_Pin = GPIO_Pin_13 ;   //��д�ܽ�
	init.GPIO_Speed = GPIO_Speed_50MHz;   //��д����
	init.GPIO_Mode = GPIO_Mode_Out_PP;    //���ù���ģʽ
	GPIO_Init(GPIOC,&init); 
	
	init.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;   //��д�ܽ�
	init.GPIO_Speed = GPIO_Speed_50MHz;   //��д����
	init.GPIO_Mode = GPIO_Mode_Out_PP;    //���ù���ģʽ
	GPIO_Init(GPIOA,&init); 

	
	
	while(1){
		
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000);
		
		/*GPIO_SetBits(GPIOA,GPIO_Pin_2);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		delay_ms(1000);*/
	
	}		//�����������
}
