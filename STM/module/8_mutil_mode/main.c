#include "led.h"
#include "beep.h"
#include "servno.h"
#include "usart.h"

#include <string.h>

//输出重定向，将标准输出流的数据，通过串口进行发送
int fputc(int ch, FILE *fp)
{
	usart_put(ch);
	return 0;
}


int main()
{
	led_init();
	beep_init();
	motor_init();
	motor_start();
	
	usart_init();
	
	printf("all device init success\r\n");
	
	while(1){
		if(flag){
			printf("recv: %s\r\n", buf);
			//判断字符串
			if( strncmp(buf, "led on", 6) == 0){
				led_on();
			} else if( strncmp(buf, "led off", 7) == 0){
				led_off();
			} else if( strncmp(buf, "beep on", 7) == 0){
				beep_on();
			} else if( strncmp(buf, "beep off", 8) == 0){
				beep_off();
			} else if( strncmp(buf, "servno ", 5) == 0){
				int angle;
				sscanf(buf, "servno %d", &angle);
				printf("angle: %d\r\n", angle);
				motor_set(angle);
			} 
			
			flag = 0;
		}
	}
}
