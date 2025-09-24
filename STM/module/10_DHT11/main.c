#include <stm32f10x.h>
#include "usart.h"
#include "systick.h"

//PB8
void gpio_setIn()		//���ùܽ�Ϊ����ģʽ
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	init.GPIO_Pin = GPIO_Pin_8;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &init);
}
void gpio_setOut()		//���ùܽ�Ϊ���ģʽ
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	init.GPIO_Pin = GPIO_Pin_8;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &init);
}

int dht11_read(int *hum, int *tem)
{
	int cnt, i, j;
	char buf[5] = {0};
	
	//1�����ùܽ�Ϊ�������
	gpio_setOut();
	
	//2�����͵�ƽ������ >= 18ms (20ms)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
	systick_delay_ms(20);
	
	//3�����ߵ�ƽ 30(us)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
	systick_delay_us(30);
	
	//4�����ùܽ�Ϊ ����ģʽ
	gpio_setIn();
	
	//5����ȡ�ܽŵ�ƽ���ж�DHT11�Ƿ���Ӧ
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0){
		
		//�ȴ��͵�ƽ����
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		//�ȴ��ߵ�ƽ����
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1);
		
		for(i = 0; i < 5; i++){		//ѭ��5�ζ�ȡ 5�ֽ�����
			for(j = 7;j >= 0; j--){
				cnt = 0;
				//�ȴ�DHT11��������ʱ �͵�ƽ����
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		
				//��ȡDHT11��������ʱ �ߵ�ƽ��ʱ��
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1){
					cnt++;
					systick_delay_us(10);
				}
				if(cnt > 5){
					buf[i] = buf[i] | (1 << j);
				}
			}
		}
		//У��5�ֽ���ǰ 4�ֽ�֮�͵ĵ� 8λ �Ƿ���� ��5�ֽ�
		if( ((buf[0]+buf[1]+buf[2]+buf[3]) & 0xff) == buf[4]){
			*hum = buf[0];
			*tem = buf[2];
			return 0;
		}
	}
	return -1;
}

int main()
{
	systick_init();
	usart_init();
	systick_delay_ms(2000);
	
	printf("all device init success\r\n");
	while(1){
		int tem, hum;
		if( dht11_read(&hum, &tem) == 0){
			printf("tem: %d, hum: %d\r\n", tem, hum);
		}
		
	}
}
