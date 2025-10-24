// delay.c
#include "delay.h"

static uint32_t fac_us = 0;     // 微秒延时系数（根据HCLK计算）

void delay_init(void) {
  // 计算微秒延时系数：HCLK频率（Hz）/ 1e6 → 1us对应的节拍数
  fac_us = HAL_RCC_GetHCLKFreq() / 1000000;
}

void delay_us(uint32_t us) {
  uint32_t start_val, current_val, ticks;
  // SysTick计数器从 reload 递减到0，重载值为SysTick->LOAD
  start_val = SysTick->VAL;
  ticks = us * fac_us;          // 需要的总节拍数

  while (1) {
    current_val = SysTick->VAL;
    // 计算已过去的节拍数（处理下溢情况）
    if (current_val < start_val) {
		
      if ((start_val - current_val) >= ticks) break;
    } else {
      // 下溢时：已过节拍 = (start_val + (LOAD - current_val))
      if ((start_val + (SysTick->LOAD - current_val)) >= ticks) break;
    }
  }
}

void delay_ms(uint32_t ms) {
  HAL_Delay(ms);  // 直接复用HAL库毫秒延时（基于SysTick中断）
}
