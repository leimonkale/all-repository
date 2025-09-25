#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>

char buf[32];
int flag = 0 ;
static int index = 0;


void delay_us(uint32_t us) {
    uint32_t ticks = us * (72 / 8); 
    while(ticks--);
}

void delay_ms(uint32_t ms) {
    while(ms--) delay_us(1000);
}

char usart_recv()
{
    while(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));  
    return USART_ReceiveData(USART1);
}

void usart_put(uint16_t ch){
	
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
	USART_SendData(USART1,ch);

}

int fputc(int ch,FILE *fp)
{
	usart_put(ch);
	return 0;
}

void usart_send(char *src)
{
    while(*src)
        usart_put(*src++);
}

void USART1_IRQHandler() {
    // ������"���շǿ�"�жϣ�USART_IT_RXNE��
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){  
        buf[index] = USART_ReceiveData(USART1);
        // ��⵽���з������ָ�����
        if(buf[index] == '\n'){  
            flag = 1;
            buf[index] = '\0';  // �滻���з�Ϊ�ַ���������
            index = 0;          // ����������׼���´ν���
        } else {
            // ��ֹ�����������������buf���ȣ�����������
            if(index < 31){  // ����buf[32]����1λ��'\0'
                index++;
            } else {
                index = 0;  // ��������ã�����Խ��
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);  // ��������жϱ�־
    }
    // �����жϣ��������������ڴ˴�������ԣ���Ӱ������߼���
}

int main(){
	//int i;
	GPIO_InitTypeDef init;
	GPIO_InitTypeDef init1;
	GPIO_InitTypeDef init2;
	TIM_TimeBaseInitTypeDef tim;
	TIM_OCInitTypeDef oc;
	USART_InitTypeDef uInit;
	NVIC_InitTypeDef nvic;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	init.GPIO_Pin = GPIO_Pin_13;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&init);
	
	init1.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
	init1.GPIO_Speed = GPIO_Speed_50MHz;
	init1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&init1);
	
	init1.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_9|GPIO_Pin_11;
	init1.GPIO_Speed = GPIO_Speed_50MHz;
	init1.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&init1);
	
	init2.GPIO_Pin = GPIO_Pin_10;
	init2.GPIO_Speed = GPIO_Speed_50MHz;
	init2.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&init2);
	
	
	tim.TIM_Prescaler = 71;
	tim.TIM_Period = 19999;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&tim);
	TIM_TimeBaseInit(TIM1,&tim);
	
	oc.TIM_Pulse = 15000;
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	oc.TIM_OutputState = ENABLE;
	TIM_OC1Init(TIM3,&oc);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4Init(TIM1,&oc);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
	
	nvic.NVIC_IRQChannel = USART1_IRQn;     
	nvic.NVIC_IRQChannelPreemptionPriority=0;     
	nvic.NVIC_IRQChannelSubPriority = 1;          
	nvic.NVIC_IRQChannelCmd = ENABLE;            
	NVIC_Init(&nvic);
	
	uInit.USART_BaudRate = 115200;
	uInit.USART_WordLength = USART_WordLength_8b;
	uInit.USART_StopBits = USART_StopBits_1;
	uInit.USART_Parity = USART_Parity_No;
	uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //���ͽ���ʹ��
	USART_Init(USART1, &uInit);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1,ENABLE);
	
	
	while(1){

		/*TIM_SetCompare1(TIM3, 500);   // �ߵ�ƽ0.5ms�����ת0��
        delay_ms(600);
        TIM_SetCompare1(TIM3, 2500);  // �ߵ�ƽ2.5ms�����ת180��
        delay_ms(600);
		
		for(i=0;i<3;i++){
		GPIO_SetBits(GPIOC,GPIO_Pin_13);    //�ߵ�ƽ
		delay_ms(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);  //�͵�ƽ
		delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		delay_ms(1000);
		}*/
		
		if(flag == 1){
			flag = 0;  // ���ñ�־
			usart_send("You received: ");
			usart_send(buf);
			usart_send("\r\n");
			
			// ʾ�������ݽ����������LED������RX+TX������
			if(strcmp(buf, "LED_ON\r") == 0){
				GPIO_SetBits(GPIOA, GPIO_Pin_1);  // ����PA1 LED
				usart_send("LED1 ON\r\n");
			} else if(strcmp(buf, "LED_OFF\r") == 0){
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // Ϩ��PA1 LED
				usart_send("LED1 OFF\r\n");
			}else if(strcmp(buf, "ENGIN\r") == 0){
					TIM_SetCompare1(TIM3, 500);   // �ߵ�ƽ0.5ms�����ת0��
					delay_ms(800);
					TIM_SetCompare1(TIM3, 2500);  // �ߵ�ƽ2.5ms�����ת180��
					delay_ms(800);
					TIM_SetCompare1(TIM3, 500);   // �ߵ�ƽ0.5ms�����ת0��
					delay_ms(800);
					TIM_SetCompare1(TIM3, 2500);  // �ߵ�ƽ2.5ms�����ת180��
					delay_ms(800);
					TIM_SetCompare1(TIM3, 500);   // �ߵ�ƽ0.5ms�����ת0��
					delay_ms(800);
					TIM_SetCompare1(TIM3, 2500);  // �ߵ�ƽ2.5ms�����ת180��
					delay_ms(800);
				
			}else if(strcmp(buf, "BEE\r") == 0){
				usart_send("BEE OFF\r\n");
				TIM_SetAutoreload(TIM1,1000);
				TIM_SetCompare4(TIM1, 500);
				TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Enable);
				delay_ms(3000);
				TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Disable);
				
			}
			else{
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);
				usart_send("LED1 ON\r\n");
			}
		}
		
		
	
	}
	
	

}
