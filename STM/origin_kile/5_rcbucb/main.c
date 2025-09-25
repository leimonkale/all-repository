#include "stm32f10x.h"                  // Device headerint
#include <stdio.h>
void usart_init()
{
	GPIO_InitTypeDef init;
	USART_InitTypeDef uInit;
	//1����ʼ���ⲿʱ�� PA9 ->  USART1_Tx  PA10  -> USART1_Rx
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

	//2���ܽų�ʼ��
	init.GPIO_Pin = GPIO_Pin_9;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������  USART1_Tx
	GPIO_Init(GPIOA, &init);

	init.GPIO_Pin = GPIO_Pin_10;
	init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���ø�������  USART1_Rx
	GPIO_Init(GPIOA, &init);
	
	//3�����ڳ�ʼ�� (���ô��ڵ�Э�飺�����ʣ�115200������λ��8 λ��ֹͣλ��1 λ��У��λ���ޡ�Ӳ�����أ���)
	uInit.USART_BaudRate = 115200;
	uInit.USART_WordLength = USART_WordLength_8b;
	uInit.USART_StopBits = USART_StopBits_1;
	uInit.USART_Parity = USART_Parity_No;
	uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //���ͽ���ʹ��
	USART_Init(USART1, &uInit);
	
	USART_Cmd(USART1,ENABLE);      //ʹ�ܴ���1
}

char usart_recv()
{
    while(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));      //��ѯ���жϽ�����ɱ�־�Ƿ���λ
    return USART_ReceiveData(USART1);
}

void usart_put(uint16_t ch){
	
	// �жϷ������ݼĴ���Ϊ�ձ�־: RESET:��־û��λ����Ϊ��    SET:��־��λ��Ϊ��
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
	//�������ݣ��ܻὫ������д�뷢�����ݼĴ���
	USART_SendData(USART1,ch);

}

int fputc(int ch,FILE *fp)
{
	usart_put(ch);
	return 0;
}

void delay(int ms){
	int i;
	while(ms--)
		for(i = 0; i < 8050;i ++);

}

void usart_send(char *src)
{
    while(*src)
        usart_put(*src++);
}

int main(){
	
	char buf[32]={0};
	int index;
	int a = 10,b = 20;
	usart_init();
	usart_send("hello world\r \n");
	
	while(1){
	
	//usart_put(usart_recv());
		//printf("a:%d,b:%d\r\n",a,b);
		buf[index] = usart_recv();
		if(buf[index] == '\n'){
			printf("recv:%s\r\n",buf);
			index = 0;
			continue;
		
		}
		index++;
		
		
	}


}

