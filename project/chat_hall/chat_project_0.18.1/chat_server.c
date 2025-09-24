#include "functions.h"

int online_count = 0;

struct status{
    int online;
    int vip;
    int busy;
    int away;
    int team;
};

typedef struct {
    struct sockaddr_in client_addr;
    char nickname[40];
    int  uid;
    struct status user_state;
    char* file[20];
    int filenum;
    char* vipfile[20];
}user;

user users[BODY_MAX];
user user0[1];

int login_judgment(struct sockaddr_in client_addr)
{
    for (int i = 0; i < online_count; i++) {
        // 比较IP和端口
        if (users[i].client_addr.sin_addr.s_addr == client_addr.sin_addr.s_addr &&
            users[i].client_addr.sin_port == client_addr.sin_port) {
            return i;  // 找到，返回标号
        }
    }return -1;
}

int user_nickname_judgment(char *chr)
{
    for (int i = 0; i < online_count; i++) {
        // 比较IP和端口
        if (strcmp(users[i].nickname,chr) == 0) {
            return i;  // 找到，返回标号
        }
    }return -1;
}

int callback(void* data, int l, char*argv[], char*c[])
{
	*((int*)data) = 1;

	return 0;
}

typedef struct{
    struct sockaddr_in clientA;
    struct sockaddr_in clientB;
}pipe_file;

int main()
{ 
    int fd[2];
	pipe(fd);
	signal(SIGCHLD, SIG_IGN);
	pid_t pid = fork();
	if(pid == 0){
    while(1){
        close(fd[1]);
        pipe_file clientAB_addr;
        char buf_file[BUFFER_SIZE];
        int sockfd_fileA = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd_fileA == -1){
            perror("socket");
            continue;
        }
        int sockfd_fileB = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd_fileB == -1){
            perror("socket");
            continue;
        }
        
        read(fd[0],&clientAB_addr,sizeof(clientAB_addr));
        struct sockaddr_in clientA_addr;
        clientA_addr.sin_family = AF_INET;
        clientA_addr.sin_port   = htons(htonl(clientAB_addr.clientA.sin_port)+1);
        clientA_addr.sin_addr.s_addr = clientAB_addr.clientA.sin_addr.s_addr;
        struct sockaddr_in clientB_addr;
        clientB_addr.sin_family = AF_INET;
        clientB_addr.sin_port   = htons(htonl(clientAB_addr.clientB.sin_port)+1);
        clientB_addr.sin_addr.s_addr = clientAB_addr.clientB.sin_addr.s_addr;
        int ret_A = connect(sockfd_fileA, (struct sockaddr*)&clientA_addr, sizeof(clientA_addr));
        if(-1 == ret_A){
		    perror("accept");
		    continue;
	    }
        else{
            send(sockfd_fileA,"send",sizeof("recv"),0);
            printf("accept success\n");
            FILE *buffer_file = fopen("buffer_file.txt","w+");
            while(1){
                memset(buf_file, 0, BUFFER_SIZE);  
                ssize_t ret_clinentA = recv(sockfd_fileA,buf_file,BUFFER_SIZE,0);
                if(fwrite(buf_file,1,ret_clinentA,buffer_file)){
                    perror("fwrite");
                    break;
                }
                fflush(buffer_file);  
                if(ret_clinentA == -1){
                    perror("recv");
                    break;
                }
                if(ret_clinentA == 0){
                    break;
                }
            }
            fclose(buffer_file);
		}
        close(sockfd_fileA);

        int ret_B = connect(sockfd_fileB, (struct sockaddr*)&clientB_addr, sizeof(clientB_addr));
        if(ret_B == -1){
            perror("connect");
            continue;
        }
        else{
            send(sockfd_fileB,"send",sizeof("send"),0);
            memset(buf_file, 0, BUFFER_SIZE);
            FILE *buffer_file = fopen("buffer_file.txt","r+");
            printf("accept success\n");
            while(1){
                ssize_t ret_file = fread(buf_file,1,BUFFER_SIZE,buffer_file);
                if(ret_file == -1){
                    perror("read");
                    break;
                }
                if(ret_file == 0){
                    break;
                }
                ssize_t ret_clientB = send(sockfd_fileB,buf_file,ret_file,0);
                if(ret_clientB == -1){
                    perror("send");
                    break;
                }
            }
            fclose(buffer_file);
        }
        close(sockfd_fileB);
    }
    }
else{
    close(fd[0]);
    char buf[BUFFER_SIZE];
    int sockfd;
    int broadcast_sockfd;
    socklen_t len;
    socklen_t broadcast_len;
    struct sockaddr_in addr;
    struct sockaddr_in broadcast_addr;
    if(-1 == socket_server(&sockfd,&len,&addr)){
        printf("error\n");
        return 1;
    }
    if(-1 == socket_broadcast(&broadcast_sockfd,&broadcast_len,&broadcast_addr)){
        printf("error\n");
        return 1;
    }

    printf("server started,waiting for connection...\n");

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    sqlite3* db;                                                           //8888888888888888888888888888888888888888888
	if(0 != sqlite3_open("my.db", &db))
	{
		printf("open fault\n");
		return -1;
	}


	char sql[400] = "create table  if not exists user (name char, passwd char);";
	char* err;

	if(0 !=  sqlite3_exec(db, sql, NULL, NULL, &err))
	{
		printf("exec:%s\n", err);
		return -1;
	}                                                                       //88888888888888888888888888888888888888888888


    int epoll_fd = epoll_create(1);                                               ///////////////////////////////////////
    if(-1 == epoll_fd){
        perror("creat");
        close(sockfd);
        return -1;
    }

    struct  epoll_event ev,events[BODY_MAX];
    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;
    ev.data .fd = sockfd;

    if(-1 == epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sockfd,&ev)){
        perror("add");
        close(sockfd);
        close(epoll_fd);
        return -1;
    }                                                                       /////////////////////////////////////////////

    while(1){
        int nfds = epoll_wait(epoll_fd,events,BODY_MAX,-1);
            if(-1 == nfds){
                perror("wait");
                return -1;
            }
        for(int i = 0;i < nfds;i++){
            if(events[i].events & EPOLLIN){
                if(events[i].data.fd == sockfd){
                    len = sizeof(addr);
                    ssize_t n = recvfrom(sockfd,buf,BUFFER_SIZE,0,(struct sockaddr*)&client_addr,&client_addr_len);
                    printf("%s:%d",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                    if(-1 == n){
                        perror("recvfrom");
                        continue;
                    }
                    buf[n]='\0';
                    int ret = login_judgment(client_addr);
                    printf("%d\n",ret);
                    if(ret == -1)            //未登录用户
                    {
                        char* name = NULL;
                        char* passwd = NULL;

                        name = (buf);
                        char *colon = strstr(name,":");
                        if(colon == NULL){
                            strcpy(buf,"Formatted error and must contain ':'");
                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                            continue;

                        }
                        passwd = colon + 1;
                        *colon = 0;

                        sprintf(sql,"select *from user where name ='%s' and passwd='%s';",name,passwd);
                        int flag = 0;
                        if(0 != sqlite3_exec(db,sql,callback,&flag,&err)){
                            printf("exec:%s\n",err);
                            return -1;
                        }
                        if(1 == flag){
                            //登录成功获取身份，进入在线用户组
                            if(online_count > BODY_MAX){
                                strcpy(buf,"The number of people in the chat room is full.");
                                sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                continue;
                            }
                            else{
                                //初始化在线用户信息
                                users[online_count].client_addr = client_addr;
                                strncpy(users[online_count].nickname,name,39);
                                users[online_count].nickname[39] = '\0';
                                users[online_count].uid = online_count + 255;
                                users[online_count].user_state.online = 1;
                                users[online_count].user_state.vip = 0;
                                users[online_count].user_state.busy = 0;
                                users[online_count].user_state.away = 0;
                                users[online_count].user_state.team = 0;

                                printf("count%s is online(ID=%d)\n",name,users[online_count].uid);
                                memset(buf,0,BUFFER_SIZE);
                                strcpy(buf,"P");
                                ssize_t byd = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                printf("%ld\n%s\n%u\n",byd,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                                online_count++;
                            }
                        }
                        else{
                            printf("2222\n");
                            sprintf(sql,"insert into user values (\"%s\", \"%s\");",name,passwd);
                            if(0 !=  sqlite3_exec(db, sql, NULL, NULL, &err)){
                                printf("exec:%s\n", err);
                                return -1;
                            }
                            strcpy(buf,"Not registered, automatically registered.");
                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                            //注册账号
                            /*strcpy(buf,"Please adhere to community guidelines.");
                            sendto(sockfd, buf, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, client_addr_len);
                            recvfrom(sockfd, buf, BUFFER_SIZE, 0,(struct sockaddr*)&client_addr,&client_addr_len);
                            if(buf[0] == '/' && buf[1] == 'g'){
                            
                            }*/
                    
                        }
                    }
                    else{
                        //已登录用户（在线）
                        printf("aaaa\n");
                        if(buf[0] == '/' && buf[1] == 'g'){
                            printf("bbbb\n");
                            if(strlen(buf) >= 3){
                                 printf("cccc\n");
                                char result[100];
                                strcpy(result,buf+2);
                                if(strstr(result,"help")){
                                    FILE *manual = fopen("manual.txt","r");
                                    if(manual == NULL){
                                        perror("fopen");
                                        strcpy(buf,"unknow erro");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    size_t ia = fread(buf,1,sizeof(buf)-1,manual);
                                    buf[ia] = '\0';
                                    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                    fclose(manual);
                                }
                                if(strstr(result,"sendmessege")){
                                    printf("3333\n");
                                    char *messege = NULL;
                                    char *body = NULL;
                                    
                                    char *colon1 = strstr(result,"/@");
                                    if( colon1 == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of one addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    char *colon2 = strstr(colon1+2,"/@");
                                    if( colon2 == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of two addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    *colon1 = '\0';
                                    *colon2 = '\0';
                                    messege = colon1 + 2;
                                    body = colon2 + 2;
                                    if(*messege == '\0' || *body == '\0'){
                                        strcpy(buf,"the messege or a is void");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    int ret = user_nickname_judgment(body);
                                    if(ret == -1){
                                        strcpy(buf,"no search the nikename");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                    }
                                    else{
                                        char chr[2048];
                                        snprintf(chr, sizeof(chr), "message privately from %s:%s", users[ret].nickname,messege);
                                        strcpy(buf,chr);
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&users[ret].client_addr, sizeof(users[ret].client_addr));
                                    }
                                }
                                if(strstr(result,"seefile")){
                                    sprintf(buf, "Number of %s's documents:%d", users[ret].nickname,users[ret].filenum);
                                    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
                                    for(int i = 0 ; i <= users[ret].filenum;i++){
                                        if(i == 0){
                                            strcpy(buf,users[ret].file[i]);
                                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
                                        }
                                        if(i>0){
                                            strcpy(buf,users[ret].vipfile[i-1]);
                                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
                                        }
                                    }
                                    continue;
                                }
                                if(strstr(result,"sendfile")){
                                    char *file_send = NULL;
                                    char *body = NULL;
                                    
                                    char *colon1 = strstr(result,"/@");
                                    if( colon1 == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of one addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    char *colon2 = strstr(colon1+2,"/@");
                                    if( colon2 == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of two addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    *colon1 = '\0';
                                    *colon2 = '\0';
                                    file_send = colon1 + 2;
                                    body = colon2 + 2;
                                    int clientB_num = user_nickname_judgment(body);
                                    if(clientB_num == -1){
                                        strcpy(buf,"nobody is this nickname or it is offline");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    if(clientB_num == ret){
                                        if(users[ret].filenum == 1){
                                            if(users[ret].user_state.vip > 0){
                                                //pipe_file client_file;
                                                //client_file.clientA = client_addr;
                                                //write(fd[1],&client_file,sizeof(client_file));
                                                users[ret].filenum++;
                                                users[ret].vipfile[users[ret].filenum-1] = file_send;
                                            }
                                            else{
                                                strcpy(buf,"sorry,your file is reach the limit,please pay the vip to expand upper limit");
                                                sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                            }
                                        }
                                        if(users[ret].filenum == 0){
                                            //pipe_file client_file;
                                            //client_file.clientA = client_addr;
                                            //write(fd[1],&client_file,sizeof(client_file));
                                            users[ret].filenum++;
                                            users[ret].file[users[ret].filenum-1] = file_send;
                                        }
                                    }
                                    else{
                                        if(users[clientB_num].filenum == 1){
                                            if(users[clientB_num].user_state.vip > 0){
                                                //pipe_file client_file;
                                                //client_file.clientA = client_addr;
                                                //write(fd[1],&client_file,sizeof(client_file));
                                                users[clientB_num].filenum++;
                                                users[clientB_num].vipfile[users[clientB_num].filenum-1] = file_send;
                                            }
                                            else{
                                                strcpy(buf,"sorry,your friend's file is reach the limit,please pay the vip to expand upper limit whith your friend");
                                                sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                            }
                                        }
                                        if(users[clientB_num].filenum == 0){
                                            //pipe_file clientAB_file;
                                            //clientAB_file.clientA = client_addr;
                                            //clientAB_file.clientB = users[clientB_num].client_addr;
                                            //write(fd[1],&clientAB_file,sizeof(clientAB_file));
                                            users[clientB_num].filenum++;
                                            users[clientB_num].file[users[clientB_num].filenum-1] = file_send;
                                        }
                                        //pipe_file clientAB_file;
                                        //clientAB_file.clientA = client_addr;
                                        //clientAB_file.clientB = users[clientB_num].client_addr;
                                        //write(fd[1],&clientAB_file,sizeof(clientAB_file));
                                        //users[clientB_num].filenum++;
                                        //users[clientB_num].file[users[clientB_num].filenum-1] = file_send;
                                    }
                                }
                                if(strstr(result,"exit")){
                                    strcpy(buf,"0000/exit/0000");
                                    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                    if(ret == (BODY_MAX - 1)){
                                        users[ret] = user0[0];
                                        online_count--; 
                                    }
                                    else{
                                        for(int i = ret;i < (online_count-1);i++){
                                            users[i]=users[i+1];
                                        }
                                        online_count--;
                                    }

                                }
                                if(strstr(result,"teamup")){
                                    char *team = NULL;
                                    char *colon = strstr(result,"/@");
                                    if( colon == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of one addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    *colon = '\0';
                                    team = colon + 2;
                                    users[ret].user_state.team = atoi(team);
                                    printf("injoin team%s success\n",team);
                                    strcpy(buf,"systeam messege :injoin success");
                                    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                }
                                if(strstr(result,"sendteam")){
                                    char *messege = NULL;
                                    char *team = NULL;
                                    char *colon1 = strstr(result,"/@");
                                    if( colon1 == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of one addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    char *colon2 = strstr(colon1+2,"/@");
                                    if( colon2 == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of two addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    *colon1 = '\0';
                                    *colon2 = '\0';
                                    messege = colon1 + 2;
                                    team = colon2 + 2;
                                    int teamnum = atoi(team);
                                    for(int i = 0;i<online_count;i++){
                                        if(users[i].user_state.team == teamnum){
                                            char chr[2048];
                                            snprintf(chr, sizeof(chr), "team segess:%s", messege);
                                            strcpy(buf,chr);
                                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&users[i].client_addr, sizeof(users[i].client_addr));
                                        }
                                    }
                                    
                                }
                                if(strstr(result,"vip")){
                                    char *vip = NULL;
                                    char *colon = strstr(result,"/@");
                                    if( colon == NULL){
                                        strcpy(buf,"Formatted error and must contain '/@' of one addr");
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                        continue;
                                    }
                                    *colon = '\0';
                                    vip = colon + 2;
                                    users[ret].user_state.vip= atoi(vip);
                                    strcpy(buf,"thank you for you pay");
                                    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                                }
                            }//附加功能（/g指令）
                            if(1){
                                printf("%s\n",buf);
                                strcpy(buf,"void cmd");
                                sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                            }
                        }
                        else{
                            if(users[ret].user_state.vip == 1){
                                char chr[2048];
                                snprintf(chr, sizeof(chr), "vip user's broadcast segess:%s", buf);
                                strcpy(buf,chr);
                                sendto(broadcast_sockfd, buf,BUFFER_SIZE, 0, (struct sockaddr*)&broadcast_addr, broadcast_len);
                            }
                            char chr[2048];
                            snprintf(chr, sizeof(chr), "%s's broadcast segess:%s", users[ret].nickname,buf);
                            strcpy(buf,chr);
                            sendto(broadcast_sockfd, buf,BUFFER_SIZE, 0, (struct sockaddr*)&broadcast_addr, broadcast_len);
                        }
                        //
                    }
                }
            }
        }    
    }
    close(sockfd);
    return EXIT_SUCCESS;
}
}
