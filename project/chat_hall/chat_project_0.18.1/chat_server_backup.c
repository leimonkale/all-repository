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

int main()
{ 
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


    int fd = epoll_create(1);                                               ///////////////////////////////////////
    if(-1 == fd){
        perror("creat");
        close(sockfd);
        return -1;
    }

    struct  epoll_event ev,events[BODY_MAX];
    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;
    ev.data .fd = sockfd;

    if(-1 == epoll_ctl(fd,EPOLL_CTL_ADD,sockfd,&ev)){
        perror("add");
        close(sockfd);
        close(fd);
        return -1;
    }                                                                       /////////////////////////////////////////////

    while(1){
        int nfds = epoll_wait(fd,events,BODY_MAX,-1);
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
                            strcpy(buf,"eroor");
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
                                if(strstr(result,"send")){
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
                                        strcpy(buf,messege);
                                        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&users[ret].client_addr, sizeof(users[ret].client_addr));
                                    }
                                }
                                if(strstr(result,"sendfile")){
                                    printf("111\n");
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
                                            strcpy(buf,messege);
                                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&users[i].client_addr, sizeof(users[i].client_addr));
                                        }
                                    }
                                }
                            }//附加功能（/g指令）
                            if(1){
                                printf("%s\n",buf);
                                strcpy(buf,"void cmd");
                                sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                            }
                        }
                        else{
                            
                            printf("%s\n",buf);
                            sendto(broadcast_sockfd, buf,BUFFER_SIZE, 0, (struct sockaddr*)&broadcast_addr, broadcast_len);
                            strcpy(buf,"B");
                            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
                            printf("send success\n");
                            //广播消息
                        }
                        //聊天室
                    }
                }
            }
        }    
    }

    close(sockfd);
    return EXIT_SUCCESS;
}
