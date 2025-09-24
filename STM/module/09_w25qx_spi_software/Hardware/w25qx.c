
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
// ��оƬ�ֲ��֪
// 0XEF13,��ʾоƬ�ͺ�ΪW25Q80
// 0XEF14,��ʾоƬ�ͺ�ΪW25Q16
// 0XEF15,��ʾоƬ�ͺ�ΪW25Q32
// 0XEF16,��ʾоƬ�ͺ�ΪW25Q64
// 0XEF17,��ʾоƬ�ͺ�ΪW25Q128


// ��ȡW25QXX��״̬�Ĵ���
// ��оƬ�ֲ��֪
// BIT7  6   5   4   3   2   1   0
// SPR   RV  TB BP2 BP1 BP0 WEL BUSY
// SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
// TB,BP2,BP1,BP0:FLASH����д��������
// WEL:дʹ������
// BUSY:æ���λ(1,æ;0,����)
uint8_t W25QX_ReadSR(void)
{
    uint8_t byte = 0;
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_ReadStatusReg); // ���Ͷ�ȡ״̬�Ĵ�������
    byte = MySPI_Swap_Byte(0Xff);        
    SPI_CS_H;
    return byte;
}

//�ȴ�����
void W25QX_Wait_Busy(void)
{
    while ((W25QX_ReadSR() & 0x01) == 0x01)
        ; // �ȴ�BUSYλ���
}

void W25QX_Write_Enable(void)
{
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_WriteEnable); // ����дʹ��
    SPI_CS_H;
}

// ����һ������
// һ������= 16ҳ=16*256�ֽ�=4096�ֽ�
void W25QX_Erase_Sector(uint32_t sector_num)
{
    uint32_t addr = sector_num * 4096;
    W25QX_Write_Enable();
    W25QX_Wait_Busy();
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_SectorErase); // ������������ָ��
    MySPI_Swap_Byte((uint8_t)(addr >> 16));
    MySPI_Swap_Byte((uint8_t)(addr >> 8));
    MySPI_Swap_Byte((uint8_t)addr);
    SPI_CS_H;          // ȡ��Ƭѡ
    W25QX_Wait_Busy(); // �ȴ��������
}
// ��ȡ����
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

//��һҳ��д������
//ע��һҳΪ256�ֽڣ����ܿ�ҳ
void W25QX_Write_Page(uint8_t *data, uint32_t addr, uint16_t size)
{

    W25QX_Write_Enable();
    SPI_CS_L;
    MySPI_Swap_Byte(W25X_PageProgram); // ����дҳ����
    MySPI_Swap_Byte((uint8_t)(addr >> 16));
    MySPI_Swap_Byte((uint8_t)(addr >> 8));
    MySPI_Swap_Byte((uint8_t)addr);
    for (int i = 0; i < size; i++)
    {
        MySPI_Swap_Byte(data[i]);
    }

    SPI_CS_H;
    W25QX_Wait_Busy(); // �ȴ�д�����
}
