#ifndef __USART_H
#define __USART_H
#include "stm32f4xx_hal.h"

// 声明USART句柄（需与CubeMX配置一致）
extern UART_HandleTypeDef huart1;

// 初始化函数（波特率由参数指定，如115200）
void USART1_Init(uint32_t baudrate);

// 重定向printf到USART1（需勾选Micro LIB）
int fputc(int ch, FILE *f);

#endif
