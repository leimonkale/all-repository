// main.c
#include "main.h"
#include "ds18b20.h"
#include "delay.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;  // USART1句柄

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

int main(void) {
  // 初始化HAL库
  HAL_Init();
  
  // 配置系统时钟（由CubeMX生成，示例为168MHz）
  SystemClock_Config();
  
  // 初始化外设
  MX_GPIO_Init();       // GPIO初始化（含DS18B20引脚）
  MX_USART1_UART_Init();// USART1初始化（115200波特率）
  delay_init();         // 延时初始化
  
  // 初始化DS18B20
  uint8_t temp_init = DS18B20_Init();
  if (temp_init != 0) {
    printf("DS18B20 init failed!\r\n");
  } else {
    printf("DS18B20 init success!\r\n");
  }
  
  // 主循环：读取温度并通过串口输出
  while (1) {
    if (temp_init == 0) {
      short temp = DS18B20_ReadTemp();
      if (temp >= 0) {
        printf("Temp: %d.%d℃\r\n", temp / 10, temp % 10);
      } else {
        printf("Temp: -%d.%d℃\r\n", (-temp)/10, (-temp)%10);
      }
    }
    HAL_Delay(1000);  // 1秒刷新一次
  }
}

// USART1初始化（PA9=TX，PA10=RX，115200波特率）
static void MX_USART1_UART_Init(void) {
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;  // 收发模式
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK) {
    Error_Handler();
  }
}

// GPIO初始化（自动生成，需确保DS18B20_PIN配置正确）
static void MX_GPIO_Init(void) {
  __HAL_RCC_GPIOA_CLK_ENABLE();  // 使能GPIOA时钟
  // DS18B20引脚初始化为输出（驱动中动态切换输入）
  GPIO_InitTypeDef gpio_init = {0};
  gpio_init.Pin = DS18B20_PIN;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DS18B20_PORT, &gpio_init);
}

// 系统时钟配置（168MHz，HSE作为PLL源，由CubeMX生成）
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;  // SYSCLK=336/2=168MHz
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // HCLK=168MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;   // PCLK1=42MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;   // PCLK2=84MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
}

// 重定向printf到USART1（需要勾选Use Micro LIB）
int fputc(int ch, FILE *f) {
  HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);
  return ch;
}

// 错误处理（死循环，可添加LED提示）
void Error_Handler(void) {
  while (1) { /* 错误时停留 */ }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) { /* 断言失败处理 */ }
#endif
