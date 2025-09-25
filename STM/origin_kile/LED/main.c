#include "stm32f10x.h"      //右键插入可以快速选入            // Device header

// 50MHz 主频下的粗略延时
void delay_us(uint32_t us) {
    uint32_t i;
    // 校准依据：50MHz = 50 个周期/μs，空循环单次约 10 个周期，故系数取 5（需实测微调）
    for (i = 0; i < us * 5; i++) {
        __NOP(); // 空操作，仅消耗时间
    }
}

void delay_ms(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms; i++) {
        delay_us(1000); // 复用微秒延时，实现毫秒级
    }
}

int main(){
	GPIO_InitTypeDef init;
	//1、管脚的时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//管脚的初始化
	init.GPIO_Pin = GPIO_Pin_13 ;   //填写管脚
	init.GPIO_Speed = GPIO_Speed_50MHz;   //填写速率
	init.GPIO_Mode = GPIO_Mode_Out_PP;    //设置工作模式
	GPIO_Init(GPIOC,&init); 
	
	init.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;   //填写管脚
	init.GPIO_Speed = GPIO_Speed_50MHz;   //填写速率
	init.GPIO_Mode = GPIO_Mode_Out_PP;    //设置工作模式
	GPIO_Init(GPIOA,&init); 

	
	
	while(1){
		
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000);
		
		/*GPIO_SetBits(GPIOA,GPIO_Pin_2);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		delay_ms(1000);*/
	
	}		//阻塞程序结束
}
