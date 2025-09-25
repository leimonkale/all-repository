#include "beep.h"
#include "reg.h"

//GPD0_0

void beep_init(void)
{
	GPD0CON = GPD0CON & ~(0xf<<0*4) | 0x1;
	GPD0DAT &= ~(0x1 << 0);
}

void beep_on(void)
{
#if  0
	//有源
	GPD0DAT |= (0x1 << 0);
	
#else
	
	//无源
	int t = 1000;
	int delay = 0;
	while(t--)
	{
		GPD0DAT |= (0x1 << 0);
		delay = 0xff0;
		while(delay--);
		
		GPD0DAT &= ~(0x1 << 0);
		delay = 0xff0;
		while(delay--);
	}
	
#endif
}

void beep_off(void)
{
	//有源  //无源
	GPD0DAT &= ~(0x1 << 0);
}


