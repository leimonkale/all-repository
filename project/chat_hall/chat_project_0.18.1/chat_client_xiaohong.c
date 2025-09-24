#include "functions.h"

int main()
{
	int sockfd;
	int broadcast_sockfd;
    socklen_t len;
	socklen_t broadcast_len;
    struct sockaddr_in addr;
	struct sockaddr_in broadcast_addr;
	
    if(-1 == socket_client(&sockfd,&len,&addr)){
        printf("error\n");
        return 1;
    }
	if(-1 == socket_client_broadcast(&broadcast_sockfd,&broadcast_len,&broadcast_addr)){
        printf("error\n");
        return 1;
    }

	int flag =0;
	char buf[BUFFER_SIZE];
	while(1)
	{	
		if(flag == 0){
			char name[STR_LEN];
			char passwd[STR_LEN];
			printf("input name and password\n");
			fgets(name, sizeof(name), stdin);
			*(strstr(name, "\n")) = 0;

			fgets(passwd, sizeof(passwd), stdin);
			*(strstr(passwd, "\n")) = 0;
		
			sprintf(buf, "%s:%s", name, passwd);

			sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, len);

			recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
			if(buf[0] == 'P'){
				flag = 1;
			}
			continue;
		}
		
		if(flag == 1){
			printf("wait\n");
			ssize_t n = recvfrom(broadcast_sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&broadcast_addr, &broadcast_len);
			if (n == -1) {
   		 		perror("recvfrom failed");
    			break; // 或重新连接逻辑
			}
			printf("success\n");
			buf[n] = '\0';
			puts(buf);
			continue;
		}


	}
	return 0;
}
