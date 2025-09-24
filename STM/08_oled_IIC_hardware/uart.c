#include "stm32f10x.h"                  // Device header
#include "uart.h"

void uart1_init(int BaudRate)
{
	//变量定义放到前面一起
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	
	//1.RCC  GPIOA时钟使能 usart1时钟时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	//2.GPIO  PA9-TX-复用推挽输出   PA10-RX-浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //选择引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //选择速率
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //选择模式 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  //选择引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //选择模式 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3.UART 配置波特率115200 数据位8位 停止位1位 奇偶校验无 硬件流控制无
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE); //使能
	
	//usart中断配置
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//NVIC中断配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级 只能填0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从优先级 0-15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //使能
	NVIC_Init(&NVIC_InitStructure);
}

void uart1_send_byte(char data)
{
	USART_SendData(USART1, data);
	
	//等待传输完成
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


//串口中断函数
void USART1_IRQHandler(void)
{
	char rx_data= 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		rx_data = uart1_recv_byte();
		uart1_send_byte(rx_data); //回显
		
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


//printf() -> fputc() -> 重写fputc -> uart1_send_byte()
int fputc(int c, FILE * stream)
{
	uart1_send_byte(c);
	return c;
}



