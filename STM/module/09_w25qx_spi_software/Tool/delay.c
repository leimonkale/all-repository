

#include "delay.h"

/* 配置时钟源 --> 72MHz(默认) / 8 = 9MHz，
*  滴答定时器每计数一次所需时间为 T = 1/(9MHz)s
*  T = (1/9Mhz)s = 1/9 us , 即每计数一次的时间为1/9微秒
*  换言之，记时1us需要计数9次
*/
void delay_us(uint32_t i)
{
    uint32_t temp;
    SysTick->LOAD=9*i;         
    SysTick->CTRL=0X01;        
    SysTick->VAL=0;            
    do
    {
        temp=SysTick->CTRL;    
    }
    while((temp&0x01)&&(!(temp&(1<<16))));    
    SysTick->CTRL=0;       
    SysTick->VAL=0;        
}

void delay_ms(uint32_t i)
{
    while(i--)
    {
        delay_us(1000);
    }
}
