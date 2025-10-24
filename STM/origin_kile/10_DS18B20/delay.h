// delay.h
#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx_hal.h"

void delay_init(void);          // 初始化延时函数
void delay_us(uint32_t us);     // 微秒级延时
void delay_ms(uint32_t ms);     // 毫秒级延时（基于HAL_Delay）

#endif
