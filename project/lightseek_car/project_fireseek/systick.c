#include <stm32f10x.h>


void systick_init(void)
{
    //systick 24λ ������ֵ: 16,777,215

//    SysTick_CLKSourceConfig ���� SysTick ʱ��Դ
    //SysTick ʱ��ԴΪ AHB ʱ��/8 ( 72MHz/8 = 9MHz )  
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    //SysTick->CTRL |= (1<<2);  //SysTick ʱ��ԴΪ AHB ʱ��
    
    SysTick->CTRL &= ~(1<<1); //��������0��, �������ж�
    
}


void systick_delay_us(int us)
{
    SysTick->LOAD = 9*us; //װ����
    SysTick->VAL = 0;
    SysTick->CTRL |= (1<<0); //��ʼ������
    while( (SysTick->CTRL & (1<<16)) == 0); //�ȴ�����0  �ȴ�ʱ�䵽��
    SysTick->CTRL &= ~(1<<16);
}

//ms: 0~1864
void systick_delay_ms(int ms)
{
    SysTick->LOAD = 9000*ms; //װ����
    SysTick->VAL = 0;
    SysTick->CTRL |= (1<<0); //��ʼ������
    //�ȴ�����0  �ȴ�ʱ�䵽��
    while( (SysTick->CTRL & (1<<16)) == 0);
    SysTick->CTRL &= ~(1<<16);
}
