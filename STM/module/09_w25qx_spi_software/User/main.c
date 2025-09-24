#include "stm32f10x.h"
#include <stdio.h>
#include "usart.h"
#include "spi.h"
#include "w25qx.h"
#include "delay.h"

uint16_t w25qx_id = 0;
char buf[32];
#define DEBUG 
int main(void)
{
	int n;
	Usart1_Init(115200);
	W25QX_Init();
	printf("W25QX_DEMO\n");

	while (1)
	{
		printf("1.查看设备类型 2.删除扇区  3.写入数据  4.查看数据\n");
		//scanf("%d", &n);
		while(!(USART1->SR & USART_FLAG_RXNE)); 
		n = USART_ReceiveData(USART1);
		printf("xxxxxxxxxxxxxx\n");
		switch (n)
		{
		case '1':
			W25QX_Read_ID(&w25qx_id);
			printf("flash_id:%#x\n", w25qx_id);
		case '2':
			W25QX_Erase_Sector(0); //删除0扇区
			break;
		case '3':
//			printf("输入要存储的字符串\n");
//			scanf("%s", buf);
//			printf("write:%s\n", buf);
//			W25QX_Write_Page((uint8_t *)buf, 1, sizeof(buf));
			W25QX_Write_Page((uint8_t *)"xxxxx world", 1, 11);
			break;
		case '4':
			W25QX_Read((uint8_t *)buf, 1, sizeof(buf));
#ifdef DEBUG
			for (int i = 0; i < sizeof(buf); i++)
			{
				printf("%#02X ", buf[i]);
			}
#endif
			printf("read:%s\n", buf);
			break;
		default:
			break;
		}
	}
}
