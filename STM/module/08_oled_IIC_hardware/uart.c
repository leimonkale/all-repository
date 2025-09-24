#include "stm32f10x.h"                  // Device header
#include "uart.h"

void uart1_init(int BaudRate)
{
	//��������ŵ�ǰ��һ��
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	
	//1.RCC  GPIOAʱ��ʹ�� usart1ʱ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	//2.GPIO  PA9-TX-�����������   PA10-RX-��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //ѡ������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //ѡ������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //ѡ��ģʽ �����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  //ѡ������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //ѡ��ģʽ ��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3.UART ���ò�����115200 ����λ8λ ֹͣλ1λ ��żУ���� Ӳ����������
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE); //ʹ��
	
	//usart�ж�����
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//NVIC�ж�����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� ֻ����0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ� 0-15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ʹ��
	NVIC_Init(&NVIC_InitStructure);
}

void uart1_send_byte(char data)
{
	USART_SendData(USART1, data);
	
	//�ȴ��������
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void uart1_send_str(char *str)
{
	while(*str != '\0')
	{
		uart1_send_byte(*str);
		str++;
	}
}

char uart1_recv_byte(void)
{
	return USART_ReceiveData(USART1);
}


//�����жϺ���
void USART1_IRQHandler(void)
{
	char rx_data= 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		rx_data = uart1_recv_byte();
		uart1_send_byte(rx_data); //����
		
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


//printf() -> fputc() -> ��дfputc -> uart1_send_byte()
int fputc(int c, FILE * stream)
{
	uart1_send_byte(c);
	return c;
}



