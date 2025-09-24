#include "stm32f10x.h"                  // Device header

#include "oled.h"   //128*64
#include "bmp.h"

/*******************************
*连线说明：  I2c
*1--SDA  <----->PA7
*2--SCL  <----->PA5
*3--GND <----->GND
*4--VCC <----->VCC
************************************/



void my_delay(int n);

int main(void)
{	
	u8 t;
		
	my_delay(8000);
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 

	t=' ';
	OLED_ShowCHinese(30,0,0);//华
	OLED_ShowCHinese(48,0,1);//清
	OLED_ShowCHinese(66,0,2);//远
	OLED_ShowCHinese(84,0,3);//见

	while(1) 
	{		
		OLED_Clear();
//		OLED_ShowCHinese(30,0,4);//华
//		OLED_ShowCHinese(48,0,5);//清
//		OLED_ShowCHinese(66,0,6);//远
//		OLED_ShowCHinese(84,0,7);//见
				
		OLED_ShowString(6,3,(u8 *)"0.96' OLED TEST",16);
		
		OLED_ShowString(0,6, (u8 *)"ASCII:",16);  
		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
		
		OLED_ShowString(63,6, (u8 *)"CODE:",16);
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值

		t++;
		if(t>'~') t=' ';
		
		my_delay(2000);
		
		
//		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
//		
//		my_delay(2000);
	}	  
}


void my_delay(int n)
{
	int i = 0;
	while(n--)
		for(i=0; i<8050; i++);
}


