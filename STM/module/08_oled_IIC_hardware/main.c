#include "stm32f10x.h"                  // Device header
#include "uart.h"
//#include "oled.h"   //128*64
#include "oled_i2c.h"   //128*64
#include "bmp.h"
#include "led.h"

/*******************************
*����˵����  I2c
*1--SDA  <----->PA7
*2--SCL  <----->PA5
*3--GND <----->GND
*4--VCC <----->VCC

*1--SDA  <----->PB7 / I2C1_SDA
*2--SCL  <----->PB6 / I2C1_SCL
*3--GND <----->GND
*4--VCC <----->VCC
************************************/

void my_delay(int n);

int main(void)
{	
	u8 t;
	
	led_init();
	uart1_init(115200);
	led_on();
	
	my_delay(1000);
	led_off();
	OLED_Init();			//��ʼ��OLED  
	led_on();
	OLED_Clear(); 
	my_delay(1000);
	
	printf("init ok\r\n");

	t=' ';
	OLED_ShowCHinese(30,0,0);//��
	OLED_ShowCHinese(48,0,1);//��
	OLED_ShowCHinese(66,0,2);//Զ
	OLED_ShowCHinese(84,0,3);//��

	while(1) 
	{		
		//printf("while 1\r\n");
		OLED_Clear();
		OLED_ShowCHinese(30,0,0);//��
		OLED_ShowCHinese(48,0,1);//��
		OLED_ShowCHinese(66,0,2);//Զ
		OLED_ShowCHinese(84,0,3);//��
				
		OLED_ShowString(6,3,(u8 *)"0.96' OLED TEST",16);
		
		OLED_ShowString(0,6, (u8 *)"ASCII:",16);  
		OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	   
		
		OLED_ShowString(63,6, (u8 *)"CODE:",16);
		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ

		t++;
		if(t>'~') t=' ';
		
		my_delay(2000);
		
		
		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
		
		my_delay(2000);

	}	  
}


void my_delay(int n)
{
	int i = 0;
	while(n--)
		for(i=0; i<8050; i++);
}


