#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

// 函数声明
void beep_init(void);
void beep_on(void);
void beep_off(void);
void play_custom_tone(void);  // 新增播放自定义音调序列函数声明

#endif

