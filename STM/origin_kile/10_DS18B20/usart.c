#include "usart.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "main.h"

// USART1句柄，全局变量供外部使用
UART_HandleTypeDef huart1;

// USART1初始化（PA9=TX，PA10=RX）
void USART1_Init(uint32_t baudrate) {
  // 1. 配置USART1参数
  huart1.Instance = USART1;                  // 目标为USART1
  huart1.Init.BaudRate = baudrate;           // 波特率（如115200）
  huart1.Init.WordLength = UART_WORDLENGTH_8B; // 数据位8位
  huart1.Init.StopBits = UART_STOPBITS_1;    // 停止位1位
  huart1.Init.Parity = UART_PARITY_NONE;     // 无校验位
  huart1.Init.Mode = UART_MODE_TX_RX;        // 收发模式
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE; // 无硬件流控
  huart1.Init.OverSampling = UART_OVERSAMPLING_16; // 16倍过采样
  if (HAL_UART_Init(&huart1) != HAL_OK) {
    Error_Handler(); // 初始化失败调用错误处理
  }
}

// HAL底层初始化（由HAL_UART_Init自动调用，配置GPIO和时钟）
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (uartHandle->Instance == USART1) {
    // 1. 使能USART1和GPIOA时钟（HAL时钟使能函数）
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 2. 配置PA9（TX）和PA10（RX）为复用功能
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;     // 复用推挽（TX）
    GPIO_InitStruct.Pull = GPIO_NOPULL;         // 无上下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 高速
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1; // 复用为USART1（AF7）
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}
