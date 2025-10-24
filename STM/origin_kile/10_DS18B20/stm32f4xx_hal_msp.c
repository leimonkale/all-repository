// stm32f4xx_hal_msp.c：硬件底层初始化
#include "main.h"

// 仅保留UART解初始化函数（若需）
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart) {
  if (huart->Instance == USART1) {
    __HAL_RCC_USART1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
  }
}
