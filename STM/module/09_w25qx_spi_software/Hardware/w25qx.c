
#include "spi.h"
#include "w25qx.h"

void W25QX_Init(void)
{
    MySPI_Init();
}
void W25QX_Read_ID(uint16_t *typeid)
{
    uint16_t Temp = 0;
    MySPI_Start();
    MySPI_Swap_Byte(W25X_ManufactDeviceID); 

    MySPI_Swap_Byte(0x00);
    MySPI_Swap_Byte(0x00);
    MySPI_Swap_Byte(0x00);

    Temp |= MySPI_Swap_Byte(0xFF) << 8;
    Temp |= MySPI_Swap_Byte(0xFF);

    *typeid = Temp;
    MySPI_Stop();
}
// 查芯片手册可知
// 0XEF13,表示芯片型号为W25Q80
// 0XEF14,表示芯片型号为W25Q16
// 0XEF15,表示芯片型号为W25Q32
// 0XEF16,表示芯片型号为W25Q64
// 0XEF17,表示芯片型号为W25Q128


// 读取W25QXX的状态寄存器
// 查芯片手册可知
// BIT7  6   5   4   3   2   1   0
// SPR   RV  TB BP2 BP1 BP0 WEL BUSY
// SPR:默认0,状态寄存器保护位,配合WP使用
// TB,BP2,BP1,BP0:FLASH区域写保护设置
// WEL:写使能锁定
// BUSY:忙标记位(1,忙;0,空闲)
uint8_t W25QX_ReadSR(void)
{
    uint8_t byte = 0;
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_ReadStatusReg); // 发送读取状态寄存器命令
    byte = MySPI_Swap_Byte(0Xff);        
    SPI_CS_H;
    return byte;
}

//等待空闲
void W25QX_Wait_Busy(void)
{
    while ((W25QX_ReadSR() & 0x01) == 0x01)
        ; // 等待BUSY位清空
}

void W25QX_Write_Enable(void)
{
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_WriteEnable); // 发送写使能
    SPI_CS_H;
}

// 擦除一个扇区
// 一个扇区= 16页=16*256字节=4096字节
void W25QX_Erase_Sector(uint32_t sector_num)
{
    uint32_t addr = sector_num * 4096;
    W25QX_Write_Enable();
    W25QX_Wait_Busy();
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_SectorErase); // 发送扇区擦除指令
    MySPI_Swap_Byte((uint8_t)(addr >> 16));
    MySPI_Swap_Byte((uint8_t)(addr >> 8));
    MySPI_Swap_Byte((uint8_t)addr);
    SPI_CS_H;          // 取消片选
    W25QX_Wait_Busy(); // 等待擦除完成
}
// 读取数据
void W25QX_Read(uint8_t *data, uint32_t addr, uint32_t size)
{
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_ReadData);
    MySPI_Swap_Byte((uint8_t)(addr >> 16));
    MySPI_Swap_Byte((uint8_t)(addr >> 8));
    MySPI_Swap_Byte((uint8_t)addr);
    for (int i = 0; i < size; i++)
    {
        *data = MySPI_Swap_Byte(0xFF);
        data++;
    }
    SPI_CS_H;
}

//在一页内写入数据
//注意一页为256字节，不能跨页
void W25QX_Write_Page(uint8_t *data, uint32_t addr, uint16_t size)
{

    W25QX_Write_Enable();
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_PageProgram); // 发送写页命令
    MySPI_Swap_Byte((uint8_t)(addr >> 16));
    MySPI_Swap_Byte((uint8_t)(addr >> 8));
    MySPI_Swap_Byte((uint8_t)addr);
    for (int i = 0; i < size; i++)
    {
        MySPI_Swap_Byte(data[i]);
    }

    SPI_CS_H;
    W25QX_Wait_Busy(); // 等待写入结束
}
