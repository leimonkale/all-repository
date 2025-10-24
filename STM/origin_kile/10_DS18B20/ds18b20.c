// ds18b20.c
#include "ds18b20.h"
#include "delay.h"

// 内部函数：切换GPIO为输出模式
static void DS18B20_SetOutput(void) {
  GPIO_InitTypeDef gpio_init = {0};
  gpio_init.Pin = DS18B20_PIN;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;  // 推挽输出
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DS18B20_PORT, &gpio_init);
}

// 内部函数：切换GPIO为输入模式
static void DS18B20_SetInput(void) {
  GPIO_InitTypeDef gpio_init = {0};
  gpio_init.Pin = DS18B20_PIN;
  gpio_init.Mode = GPIO_MODE_INPUT;      // 浮空输入
  gpio_init.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DS18B20_PORT, &gpio_init);
}

// 内部函数：复位传感器
static uint8_t DS18B20_Reset(void) {
  uint8_t ack = 1;  // 应答标志（1=无应答，0=有应答）
  
  DS18B20_CLK_EN();       // 使能GPIO时钟
  DS18B20_SetOutput();
  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);  // 拉低总线
  delay_us(480);          // 至少拉低480us
  
  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);    // 释放总线
  delay_us(60);           // 等待60us（传感器应答窗口）
  
  DS18B20_SetInput();
  if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN) == GPIO_PIN_RESET) {
    ack = 0;              // 传感器拉低总线，应答成功
  }
  delay_us(420);          // 等待剩余时间（确保总线恢复）
  return ack;
}

// 内部函数：向传感器写1字节
static void DS18B20_WriteByte(uint8_t data) {
  DS18B20_SetOutput();
  for (uint8_t i = 0; i < 8; i++) {
    // 每bit起始：拉低总线1us
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    delay_us(1);
    
    // 写数据：1=释放总线，0=保持拉低
    if (data & 0x01) {
      HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    }
    delay_us(60);         // 保持60us（满足时序要求）
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);    // 释放总线
    data >>= 1;           // 处理下一位
  }
}

// 内部函数：从传感器读1字节
static uint8_t DS18B20_ReadByte(void) {
  uint8_t data = 0;
  DS18B20_SetOutput();
  
  for (uint8_t i = 0; i < 8; i++) {
    // 每bit起始：拉低总线1us
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    delay_us(1);
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);    // 释放总线
    delay_us(1);         // 等待1us后读取
    
    DS18B20_SetInput();
    if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN) == GPIO_PIN_SET) {
      data |= (1 << i);   // 读取到1
    }
    delay_us(60);         // 保持60us
  }
  return data;
}

// 初始化DS18B20（返回0=成功，1=失败）
uint8_t DS18B20_Init(void) {
  return DS18B20_Reset();  // 复位成功即初始化成功
}

// 读取温度（返回值：0.1℃为单位，如255→25.5℃，-123→-12.3℃）
short DS18B20_ReadTemp(void) {
  uint8_t temp_l, temp_h;
  short temp;
  
  DS18B20_Reset();
  DS18B20_WriteByte(0xCC);  // 跳过ROM（单传感器时用）
  DS18B20_WriteByte(0x44);  // 启动温度转换
  delay_ms(750);            // 等待转换完成（最大750ms）
  
  DS18B20_Reset();
  DS18B20_WriteByte(0xCC);  // 跳过ROM
  DS18B20_WriteByte(0xBE);  // 读取温度寄存器
  
  temp_l = DS18B20_ReadByte();  // 低8位（含小数部分）
  temp_h = DS18B20_ReadByte();  // 高8位（含符号位）
  temp = (temp_h << 8) | temp_l;
  
  // 转换为0.1℃：DS18B20精度0.0625℃ → ×625/1000 = ×5/8
  if (temp < 0) {  // 负温度处理（补码转原码）
    temp = ~temp + 1;  // 取绝对值
    return -((temp * 5) / 8);
  } else {
    return (temp * 5) / 8;
  }
}
