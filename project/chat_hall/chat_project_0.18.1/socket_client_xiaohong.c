#include "functions.h"

int socket_client(int *sockfd,socklen_t *len,struct sockaddr_in *addr)
{
    *sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == *sockfd){
        perror("socket");
        return -1;
    }

    memset(addr,0,sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port   = htons(PORT_SERVER);
    addr->sin_addr.s_addr = inet_addr(IP_CLIENT);
    *len = sizeof(*addr);

    return 0;
}

int socket_client_broadcast(int *sockfd,socklen_t *len,struct sockaddr_in *addr)
{
    *sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == *sockfd){
        perror("socket");
        return -1;
    }

    memset(addr,0,sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port   = htons(PORT_BROADCAST);
    addr->sin_addr.s_addr = inet_addr(IP_SERVER);
    *len = sizeof(*addr);

    if(-1 == bind(*sockfd, (struct sockaddr*)addr, sizeof(*addr)))
	{
		perror("bind");
		return -1;
	}

    return 0;
}