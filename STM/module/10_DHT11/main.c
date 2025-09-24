#include <stm32f10x.h>
#include "usart.h"
#include "systick.h"

//PB8
void gpio_setIn()		//设置管脚为输入模式
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	init.GPIO_Pin = GPIO_Pin_8;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &init);
}
void gpio_setOut()		//设置管脚为输出模式
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
	
	//1、设置管脚为输出功能
	gpio_setOut();
	
	//2、拉低电平，持续 >= 18ms (20ms)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
	systick_delay_ms(20);
	
	//3、拉高电平 30(us)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
	systick_delay_us(30);
	
	//4、设置管脚为 输入模式
	gpio_setIn();
	
	//5、读取管脚电平，判断DHT11是否响应
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0){
		
		//等待低电平结束
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		//等待高电平结束
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1);
		
		for(i = 0; i < 5; i++){		//循环5次读取 5字节数据
			for(j = 7;j >= 0; j--){
				cnt = 0;
				//等待DHT11发送数据时 低电平结束
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		
				//读取DHT11发送数据时 高电平的时长
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1){
					cnt++;
					systick_delay_us(10);
				}
				if(cnt > 5){
					buf[i] = buf[i] | (1 << j);
				}
			}
		}
		//校验5字节中前 4字节之和的低 8位 是否等于 第5字节
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
