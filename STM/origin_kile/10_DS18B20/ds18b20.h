// ds18b20.h
#ifndef __DS18B20_H
#define __DS18B20_H
#include "stm32f4xx_hal.h"

// 配置DS18B20连接的GPIO（需与CubeMX一致，示例：PA0）
#define DS18B20_PORT        GPIOA
#define DS18B20_PIN         GPIO_PIN_0
#define DS18B20_CLK_EN()    __HAL_RCC_GPIOA_CLK_ENABLE()

// 函数声明
uint8_t DS18B20_Init(void);     // 初始化传感器
short DS18B20_ReadTemp(void);   // 读取温度（返回值：0.1℃为单位）

#endif
