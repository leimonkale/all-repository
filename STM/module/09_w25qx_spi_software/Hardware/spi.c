
#include "stm32f10x.h"
#include "spi.h"
#include "delay.h"

void MySPI_Init(void )
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=SPI_CS_PIN|SPI_SCK_PIN|SPI_MOSI_PIN;
    GPIO_Init(SPI_PORT,&GPIO_InitStructure);
 
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=SPI_MISO_PIN;
    GPIO_Init(SPI_PORT,&GPIO_InitStructure);
 
    SPI_CS_H; 
    SPI_SCK_L;
}
void MySPI_Start(void )
{
    SPI_CS_L; 
}

void MySPI_Stop(void )
{
    SPI_CS_H;
}
uint8_t MySPI_Swap_Byte(uint8_t Data)
{
    uint8_t temp=0x00;
    
    //SPI模式0 MSB 高位先行
    //上升沿 数据采样
    //下降沿 准备数据
    for (int i = 7; i >=0 ; i--)
    {
        SPI_MOSI_SET( Data & (0x1<<i) );    //准备数据发送 
        SPI_SCK_H ;  //拉高 发送

        //读数据
        if(SPI_MISO_READ()== Bit_SET)
        {
            temp|=(0x1<<i);
        }
        SPI_SCK_L;  //拉低  
    }
    return temp;
}


