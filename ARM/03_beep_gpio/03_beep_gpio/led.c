#include "led.h"
#include "reg.h"




void led_init(void)
{
    //GPXX_CON  -> bit -> 0001 0x1
   // int *p = (int *)0x114001e0;
   // *(int *)0x114001e0  &= ~0xf0000;

    //led5  GPF3_5
    GPF3CON = GPF3CON & ~(0xf<<5*4) | (0x1<<5*4);
    GPF3DAT &= ~(0x1<<5);

    //led4  GPF3_4
    GPF3CON = GPF3CON & ~(0xf<<4*4) | (0x1<<4*4);
    GPF3DAT &= ~(0x1<<4);


    //led3  GPX1_0
    GPX1CON = GPX1CON & ~(0xf<<0*4) | (0x1<<0*4);
    GPX1DAT &= ~(0x1<<0);

    //led4  GPX2_7
    GPX2CON = GPX2CON & ~(0xf<<7*4) | (0x1<<7*4);
    GPX2DAT &= ~(0x1<<7);
}

void led_on(LedNum  led_num)
{
    switch(led_num)
    {
        case LED2:  GPX2DAT |= (0x1<<7); break;
        case LED3:  GPX1DAT |= (0x1<<0); break;
        case LED4:  GPF3DAT |= (0x1<<4); break;
        case LED5:  GPF3DAT |= (0x1<<5); break;
    }
}

void led_off(LedNum  led_num)
{
    switch(led_num)
    {
        case LED2:  GPX2DAT &= ~(0x1<<7); break;
        case LED3:  GPX1DAT &= ~(0x1<<0); break;
        case LED4:  GPF3DAT &= ~(0x1<<4); break;
        case LED5:  GPF3DAT &= ~(0x1<<5); break;
    }
}



