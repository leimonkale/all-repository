/*===============================================
*   文件名称：reg.h
*   创 建 者：     
*   创建日期：2025年09月05日
*   描    述：
================================================*/
#ifndef __REG_H
#define __REG_H


#define GPF3CON  (*(volatile unsigned int *)0x114001e0)
#define GPF3DAT  (*(volatile unsigned int *)0x114001e4)

#define GPX1CON  (*(volatile unsigned int *)0x11000c20)
#define GPX1DAT  (*(volatile unsigned int *)0x11000c24)

#define GPX2CON  (*(volatile unsigned int *)0x11000c40)
#define GPX2DAT  (*(volatile unsigned int *)0x11000c44)

#define GPD0CON  (*(volatile unsigned int *)0x114000a0)
#define GPD0DAT  (*(volatile unsigned int *)0x114000a4)


#endif


