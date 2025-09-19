/*===============================================
*   文件名称：led.h
*   创 建 者：     
*   创建日期：2025年09月05日
*   描    述：
================================================*/

#ifndef __LED_H
#define __LED_H
/*
#define LED2 0
#define LED3 1
#define LED4 2
#define LED5 3
*/

typedef enum{
    LED2 = 0,
    LED3,
    LED4,
    LED5
}LedNum;


void led_init(void);
void led_on(LedNum  led_num);
void led_off(LedNum  led_num);


#endif

