#include "functions.h"

typedef struct {
    int sockfd;
    struct sockaddr_in server_addr;
} values_pth;
char shared_buffer[BUFFER_SIZE];
pthread_mutex_t buffer_mutex;
int buffer_flag = 0;

void *thread_function(void *arg) {
	values_pth *vp = (values_pth*)arg;
	int sockfd = vp->sockfd;
    struct sockaddr_in server_addr = vp->server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buf[BUFFER_SIZE];
	
	while(1) {
        memset(buf, 0, BUFFER_SIZE);
        recvfrom(sockfd, buf, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
		printf("%s\n",buf);
		if(strstr(buf,"0000/exit/0000")){
				break;
			}
		if(buf[0] == 'P'){
			pthread_mutex_lock(&buffer_mutex);
			strncpy(shared_buffer, buf, BUFFER_SIZE);
			buffer_flag = 1;
			pthread_mutex_unlock(&buffer_mutex);
		}
	}
	close(sockfd);
	return NULL;
}
typedef struct {
    int fd[2];
} values_fd;
void *exit_function(void *arg){
	values_fd *vfd = (values_fd*)arg;
	int read_fd = vfd->fd[0];
	char buf_fd[2];
	memset(buf_fd, 0, sizeof(buf_fd));
	read(read_fd,buf_fd,sizeof("a"));
	if(strstr(buf_fd,"a")){
		_exit(0);
	}
	return NULL;
}
	
int main()
{	
	int fd[2];
	pipe(fd);
	signal(SIGCHLD, SIG_IGN);
	pid_t pid = fork();
	if(pid == 0){
		close(fd[1]);
		char buf[BUFFER_SIZE];
		int broadcast_sockfd;
		socklen_t broadcast_len;
		struct sockaddr_in broadcast_addr;

		if(-1 == socket_client_broadcast(&broadcast_sockfd,&broadcast_len,&broadcast_addr)){
        	printf("error\n");
        	return 1;
    	}

		pthread_t thread_broadcast;
		values_fd value_fd;
		value_fd.fd[0] = fd[0];
		if (pthread_create(&thread_broadcast, NULL, exit_function, &value_fd) != 0) {
        	perror("pthread_create failed");
			close(fd[0]);
        	close(broadcast_sockfd);
        	return -1;
    	}
		
		while(1){
			printf("wait\n");
			ssize_t n = recvfrom(broadcast_sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&broadcast_addr, &broadcast_len);
			if (n == -1) {
   				perror("recvfrom failed");
			}
			puts(buf);
		}
		close(broadcast_sockfd);
	}
	else{
		close(fd[0]);
		int sockfd;
    	socklen_t len;
    	struct sockaddr_in addr;
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port   = htons(6666);
		server_addr.sin_addr.s_addr = inet_addr("192.168.2.193");
		socklen_t server_addr_len = sizeof(addr);
	
    	if(-1 == socket_client(&sockfd,&len,&addr)){
        	printf("error\n");
        	return -1;
    	}

		if (pthread_mutex_init(&buffer_mutex, NULL) != 0) {
        	perror("mutex init failed");
        	close(sockfd);
        	return -1;
		}
		pthread_t thread;
		values_pth value_pth;
    	value_pth.sockfd = sockfd;
    	value_pth.server_addr   = server_addr;
    	if (pthread_create(&thread, NULL, thread_function, &value_pth) != 0) {
        	perror("pthread_create failed");
        	close(sockfd);
        	pthread_mutex_destroy(&buffer_mutex);
        	return -1;
    	}


		FILE *flag_file = fopen("flag.bin","ab+");
		if(flag_file == NULL){
			perror("fopen");
			fclose(flag_file);
			return -1;
		}
		int flag;
		fseek(flag_file,0,SEEK_END);
		long flag_file_size = ftell(flag_file);
		if(flag_file_size == -1L){
			perror("ftell");
			fclose(flag_file);
			return -1;
		}
		if(flag_file_size == 0){
			flag = 0;
			fseek(flag_file,0,SEEK_SET);
			fwrite(&flag,sizeof(int),1,flag_file);
			fflush(flag_file);
		}
		if(flag_file_size == 4){
			fseek(flag_file,0,SEEK_SET);
			fread(&flag,sizeof(int),1,flag_file);
		}
		if(flag_file_size > 4){
			printf("flag.bin error,please restar");
			fclose(flag_file);
			flag_file = fopen("flag.bin","wb");
			fclose(flag_file);
			//清空文件
			exit(-1);
		}

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

				sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, server_addr_len);

				sleep(1);

				pthread_mutex_lock(&buffer_mutex);
				if(buffer_flag){
					printf("ssss\n");
					if(shared_buffer[0] == 'P'){
						flag = 1;
						buffer_flag = 0;
						pthread_mutex_unlock(&buffer_mutex);
						fclose(flag_file);
						flag_file = fopen("flag.bin","wb");
						fclose(flag_file);
						flag_file = fopen("flag.bin","rb+");
						fwrite(&flag,sizeof(int),1,flag_file);
						fflush(flag_file);
					}	
				}

				continue;
			}
		
			if(flag == 1){
				printf(":");
				fgets(buf, sizeof(buf), stdin);
				size_t buf_len = strlen(buf);
				buf[buf_len -1]='\0';
				if(strstr(buf,"exit")){
					printf("1111\n");
					flag = 0;
					fseek(flag_file,0,SEEK_SET);
					fwrite(&flag,sizeof(int),1,flag_file);
					fflush(flag_file);
					write(fd[1],"a",sizeof("a"));
					strcpy(buf,"/gexit");
					sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&server_addr, server_addr_len);
					break;
				}
				sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&server_addr, server_addr_len);
				continue;
			}


		}
		waitpid(pid,NULL,0);
		pthread_cancel(thread);
		pthread_join(thread, NULL);
		pthread_mutex_destroy(&buffer_mutex);
		close(sockfd);
		fclose(flag_file);
	}
	return 0;
}
