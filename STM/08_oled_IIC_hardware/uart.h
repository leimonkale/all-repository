#ifndef __UART_H
#define __UART_H

#include "stdio.h"

void uart1_init(int BaudRate);
void uart1_send_byte(char data);
char uart1_recv_byte(void);

void uart1_send_str(char *str);

#endif


