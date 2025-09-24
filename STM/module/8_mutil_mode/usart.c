#include "usart.h"


char buf[32] = {0};
int flag = 0;


void usart_init()
{
	GPIO_InitTypeDef init;
	USART_InitTypeDef uInit;
	
	nvic_init();
	
	//1����ʼ���ⲿʱ�� PA9 ->  USART1_Tx   PA10  -> USART1_Rx
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	//2���ܽų�ʼ��
	init.GPIO_Pin = GPIO_Pin_9;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������  USART1_Tx
	GPIO_Init(GPIOA, &init);
	
	init.GPIO_Pin = GPIO_Pin_10;
	init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���ø�������	USART1_Rx
	GPIO_Init(GPIOA, &init);
	
	//3�����ڳ�ʼ��(���ô��ڵ�Э�飺�����ʣ�115200������λ��8λ��ֹͣλ��1λ��У��λ���ޡ�Ӳ�����أ���)
	uInit.USART_BaudRate = 115200;
	uInit.USART_WordLength = USART_WordLength_8b;
	uInit.USART_StopBits = USART_StopBits_1;
	uInit.USART_Parity = USART_Parity_No;
	uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//���ͽ���ʹ��
	USART_Init(USART1, &uInit);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//ʹ�ܴ��ڵĽ����ж�
	
	USART_Cmd(USART1, ENABLE);		//ʹ�ܴ��� 1
}

void nvic_init()
{
	NVIC_InitTypeDef init;
	init.NVIC_IRQChannel = USART1_IRQn;		//ָ���ж�ͨ��(�ж�Դ)
	init.NVIC_IRQChannelPreemptionPriority = 0;			//������ռ���ȼ�
	init.NVIC_IRQChannelSubPriority = 1;				//���ô�ռ���ȼ�
	init.NVIC_IRQChannelCmd = ENABLE;					//�ж�ͨ��ʹ��
	NVIC_Init(&init);
}

void usart_put(uint16_t ch)
{
	// �жϷ������ݼĴ���Ϊ�ձ�־: RESET:��־û��λ����Ϊ��     SET:��־��λ��Ϊ��
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	// �������ݣ����߻Ὣ������д�� �������ݼĴ���
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

// �����жϴ�����
void USART1_IRQHandler()
{
	static int index = 0;
	//�жϵ�ǰ������ڵ��ж��Ƿ�Ϊ �����ж�
	if(USART_GetITStatus(USART1, USART_IT_RXNE)  == SET){		
		//һ��Ҫ�� ���ݶ�ȡ�������յ��ĵڶ������ݣ�������������ж�
		buf[index] = USART_ReceiveData(USART1);
		if(buf[index] == '\n'){
			buf[index] = '\0';		//��� ĩβ�� ���з� '\n'
			flag = 1;				//����һ���ַ������ݵ���ɱ�־
			index = 0;
		} else 
			index++;
		//�崦�жϱ�־�������־λ�������NVIC��ΪMCUδ������жϣ��ͻ��ٴ��ύMCU����
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
