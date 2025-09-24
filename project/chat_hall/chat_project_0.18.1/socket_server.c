#include "functions.h"

int socket_server(int *sockfd,socklen_t *len,struct sockaddr_in *addr)
{
    *sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == *sockfd){
        perror("socket");
        return -1;
    }

    memset(addr,0,sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port   = htons(PORT_SERVER);
    addr->sin_addr.s_addr = inet_addr(IP_SERVER);
    *len = sizeof(*addr);

    if(-1 == bind(*sockfd,(struct sockaddr*)addr,*len)){
        perror("bind");
        close(*sockfd);
        return -1;
    }
        return 0;
}

int socket_broadcast(int *sockfd,socklen_t *len,struct sockaddr_in *addr)
{
    *sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == *sockfd){
        perror("socket");
        return -1;
    }
    int val = 1;
	if(-1 == setsockopt(*sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val))){
		perror("setsockopt");
		return -1;
	}

    memset(addr,0,sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port   = htons(PORT_BROADCAST);
    addr->sin_addr.s_addr = inet_addr(IP_BROADCAST);
    *len = sizeof(*addr);

    return 0;
}