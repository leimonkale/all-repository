#include "stm32f10x.h"                  // Device header
#include "light.h"
#include "uart.h"


void my_delay_ms(int ms)
{
	int i = 0;
	while(ms--)
	{
		for(i=0; i<8050; i++);
	}
}

int main()
{
	char buf[64] = {0};
	int light_value = 0;

	light_init();
	uart_init(115200);
	
	light_start();

	
	while(1)
	{
		light_value = get_light_value(); 
		
		sprintf(buf, "light1: %d\n", light_value);
		uart_send_str(buf);
		

		printf("light2: %d\n", light_value);
		
		my_delay_ms(500);
	}
	
}

