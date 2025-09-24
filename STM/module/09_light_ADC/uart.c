#include "stm32f10x.h"                  // Device header
#include "uart.h"


//PA9-USART1_TX �����������     PA10-USART1_RX ��������
void uart_init(int BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//1.RCC   GPIOA  UART 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	//2.GPIO  PA9�����������   PA10��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3.uart  ������ ����λ У��λ ֹͣλ ... 
	USART_InitStructure.USART_BaudRate = BaudRate;  //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //���ݳ��� 8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ 1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;  //��żУ��λ ����
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ������ ��
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //ģʽ
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 0/1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //0~7
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4.ʹ��
	USART_Cmd(USART1, ENABLE);
}



void uart_send_byte(char data)
{
	USART_SendData(USART1, data);
	//�ȴ��������
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}

void uart_send_str(char *str)
{
	while(*str != '\0')
	{
		uart_send_byte(*str);
		str++;
	}
}

//ħ����ͼ��(options) -> target -> ��ѡUSE MicroLIB
//printf -> fputc -> uart_send_byte
int fputc(int c, FILE * stream)
{
	uart_send_byte(c);
	return 0;
}




unsigned char uart_recv_byte(void)
{
	u16 RxData; 
	
	//�ȴ��������� �����ȴ�
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);	
	
	RxData = USART_ReceiveData(USART1);
	return RxData;
}

unsigned char recv_buf[64] = {0};
int flag = 0;

void USART1_IRQHandler(void)
{
	u16 RxData; 
	static int i = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		RxData = USART_ReceiveData(USART1);
//		USART_SendData(USART1, RxData);
		
		if(RxData != '\n')
		{
			recv_buf[i++] = RxData;
		}
		else
		{
			recv_buf[i++] = '\0';
			i = 0;
			flag = 1;
		}

//		if(RxData == 0x21)//�жϰ�ͷ
//		{
//			flag = 1;
//		}

		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

void uart_get_recvbuf(unsigned char *buf)
{
	while(flag == 0);
	strcpy((char *)buf, (char *)recv_buf);
	flag = 0;	
}



