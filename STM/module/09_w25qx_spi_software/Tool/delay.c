

#include "delay.h"

/* ����ʱ��Դ --> 72MHz(Ĭ��) / 8 = 9MHz��
*  �δ�ʱ��ÿ����һ������ʱ��Ϊ T = 1/(9MHz)s
*  T = (1/9Mhz)s = 1/9 us , ��ÿ����һ�ε�ʱ��Ϊ1/9΢��
*  ����֮����ʱ1us��Ҫ����9��
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
