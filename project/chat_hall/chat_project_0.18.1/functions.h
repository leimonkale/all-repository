#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sqlite3.h>
#include <pthread.h>
#include <signal.h>

int socket_server(int *sockfd,socklen_t *len,struct sockaddr_in *addr);
int socket_client(int *sockfd,socklen_t *len,struct sockaddr_in *addr);
int socket_broadcast(int *sockfd,socklen_t *len,struct sockaddr_in *addr);
int socket_client_broadcast(int *sockfd,socklen_t *len,struct sockaddr_in *addr);

#define PORT_SERVER 6666
#define PORT_BROADCAST 8888
#define PORT_CLIENT 6667
#define IP_BROADCAST "192.168.2.255"
#define IP_CLIENT "192.168.2.193"
#define IP_SERVER "0.0.0.0"
#define BUFFER_SIZE 1024
#define STR_LEN 100
#define BODY_MAX 100

#endif