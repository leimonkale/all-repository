#ifndef USART_H
#define USART_H

#include <stm32f10x.h>
#include <stdio.h>


extern char buf[32];
extern int flag;

void usart_init(void);
void nvic_init(void);
void usart_put(uint16_t ch);
void usart_send(char *src);
int fputc(int ch, FILE *fp);
void delay(int ms);

#endif
