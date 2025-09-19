
#include "led.h"
#include "beep.h"

void sys_delay(int time);

void user_delay(int t)
{
    int i = 0;
    while(t--)
        for(i=0; i<0xff000; i++);
}


int main(void)
{ 
    led_init();
	beep_init();
	
	beep_on();
        
    while(1)
    {
        led_on(LED5);
        //sys_delay(0xff00000);
		user_delay(1);

        led_off(LED5);
        //sys_delay(0xff00000);
		user_delay(1);
    }
} 
