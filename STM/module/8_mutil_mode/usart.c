#include "usart.h"


char buf[32] = {0};
int flag = 0;


void usart_init()
{
	GPIO_InitTypeDef init;
	USART_InitTypeDef uInit;
	
	nvic_init();
	
	//1、初始化外部时钟 PA9 ->  USART1_Tx   PA10  -> USART1_Rx
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	//2、管脚初始化
	init.GPIO_Pin = GPIO_Pin_9;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出  USART1_Tx
	GPIO_Init(GPIOA, &init);
	
	init.GPIO_Pin = GPIO_Pin_10;
	init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //复用浮空输入	USART1_Rx
	GPIO_Init(GPIOA, &init);
	
	//3、串口初始化(设置串口的协议：波特率：115200、数据位：8位、停止位：1位、校验位：无、硬件流控：无)
	uInit.USART_BaudRate = 115200;
	uInit.USART_WordLength = USART_WordLength_8b;
	uInit.USART_StopBits = USART_StopBits_1;
	uInit.USART_Parity = USART_Parity_No;
	uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//发送接收使能
	USART_Init(USART1, &uInit);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//使能串口的接收中断
	
	USART_Cmd(USART1, ENABLE);		//使能串口 1
}

void nvic_init()
{
	NVIC_InitTypeDef init;
	init.NVIC_IRQChannel = USART1_IRQn;		//指定中断通道(中断源)
	init.NVIC_IRQChannelPreemptionPriority = 0;			//设置先占优先级
	init.NVIC_IRQChannelSubPriority = 1;				//设置从占优先级
	init.NVIC_IRQChannelCmd = ENABLE;					//中断通道使能
	NVIC_Init(&init);
}

void usart_put(uint16_t ch)
{
	// 判断发送数据寄存器为空标志: RESET:标志没置位，不为空     SET:标志置位，为空
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	// 发送数据，总线会将该数据写入 发送数据寄存器
	USART_SendData(USART1, ch);
}

void usart_send(char *src)
{
	while(*src)
		usart_put(*src++);
}


void delay(int ms)
{
	int i;
	while(ms--)
		for(i = 0; i < 8050; i++);
}

// 串口中断处理函数
void USART1_IRQHandler()
{
	static int index = 0;
	//判断当前这个串口的中断是否为 接收中端
	if(USART_GetITStatus(USART1, USART_IT_RXNE)  == SET){		
		//一定要将 数据读取，否则收到的第二条数据，不会产生接收中断
		buf[index] = USART_ReceiveData(USART1);
		if(buf[index] == '\n'){
			buf[index] = '\0';		//清除 末尾的 换行符 '\n'
			flag = 1;				//接收一条字符串数据的完成标志
			index = 0;
		} else 
			index++;
		//清处中断标志，如果标志位不清除，NVIC认为MCU未处理该中断，就会再次提交MCU处理
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
