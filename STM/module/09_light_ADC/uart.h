#ifndef __UART_H
#define __UART_H

#include <stdio.h>
#include <string.h>

void uart_init(int BaudRate);
void uart_send_byte(char data);
void uart_send_str(char *str);

unsigned char uart_recv_byte(void);
void uart_get_recvbuf(unsigned char *buf);

#endif
