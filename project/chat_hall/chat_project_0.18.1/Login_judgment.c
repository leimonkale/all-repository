#include "functions.h"

                    len = sizeof(addr);
                    ssize_t n = recvfrom(sockfd,buf,BUFFER_SIZE,0,(struct sockaddr*)&client_addr,&client_addr_len);
                    if(-1 == n){
                        perror("recvfrom");
                        continue;
                    }
                    buf[n]='\0';