#ifndef _W25QX_H_
#define _W25QX_H_

#include "stm32f10x.h"

//÷∏¡Ó±Ì
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void W25QX_Init(void);
void W25QX_Read_ID(uint16_t *typeid);

uint8_t W25QX_ReadSR(void);
void W25QX_Wait_Busy(void) ;
void W25QX_Write_Enable(void);   

void W25QX_Erase_Sector(uint32_t sector_num);
void W25QX_Read(uint8_t *data, uint32_t addr, uint32_t size);
void W25QX_Write_Page(uint8_t *data, uint32_t addr, uint16_t size);
#endif
