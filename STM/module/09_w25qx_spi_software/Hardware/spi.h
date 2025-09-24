#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f10x.h"

/* 通过软件实现spi驱动 */

#define SPI_PORT GPIOB
#define SPI_CS_PIN GPIO_Pin_12
#define SPI_SCK_PIN GPIO_Pin_13
#define SPI_MISO_PIN GPIO_Pin_14
#define SPI_MOSI_PIN GPIO_Pin_15

#define SPI_CS_L  GPIO_WriteBit(SPI_PORT,SPI_CS_PIN,Bit_RESET)
#define SPI_CS_H  GPIO_WriteBit(SPI_PORT,SPI_CS_PIN,Bit_SET)

#define SPI_SCK_L  GPIO_WriteBit(SPI_PORT,SPI_SCK_PIN,Bit_RESET)
#define SPI_SCK_H  GPIO_WriteBit(SPI_PORT,SPI_SCK_PIN,Bit_SET)

#define SPI_MOSI_SET(x)  (x) ? GPIO_WriteBit(SPI_PORT, SPI_MOSI_PIN, Bit_SET) : GPIO_WriteBit(SPI_PORT, SPI_MOSI_PIN, Bit_RESET) 
#define SPI_MISO_READ()  GPIO_ReadInputDataBit(SPI_PORT,SPI_MISO_PIN)

void MySPI_Init(void );
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_Swap_Byte(uint8_t Data);

#endif
