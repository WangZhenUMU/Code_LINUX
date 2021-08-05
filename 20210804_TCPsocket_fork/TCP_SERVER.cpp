#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void sigcallback(int signo)
{
    printf("recv signo : %d\n",signo);
    wait(NULL);
}
int main()
{
    signal(SIGCHLD,sigcallback);//父进程捕捉SIGCHLD信号
    //创建监听套接字
    int listen_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_sock<0)
    {
        perror("sock error!");
        return 0;
    }
    //创建sockaddr_in结构体
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(10086);
    addr.sin_addr.s_addr=inet_addr("0.0.0.0"); //0.0.0.0 本地所有网卡地址
    int ret =bind(listen_sock,(struct sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("bind error!");
        return 0;
    }
    ret = listen(listen_sock,5); //监听
    if(ret<0)
    {
        perror("listen error");
        return 0;
    }
    while(1)
    {
        // 接收套接字
        int newsockfd = accept(listen_sock,NULL,NULL);
        if(newsockfd < 0)
        {
            continue;
        }
        // 创建子进程
        int pid = fork();
        if(pid<0)
        {
            perror("fork error!");
            continue;
        }
        else if(pid == 0)
        {
            //child
            close(listen_sock);
            while(1)
            {
                char buf[1024]={0};
                ssize_t recv_size=recv(newsockfd,buf,sizeof(buf)-1,0);
                if(recv_size<0)
                {
                    perror("recv error");    
                }
                else if(recv_size==0)
                {
                    printf("peer shutdown!!\n");
                    close(newsockfd);
                    exit(1);
                }
                else 
                {
                    printf("%s\n",buf);
                    memset(buf,'\0',sizeof(buf));
                    strcpy(buf,"i am server");
                    send(newsockfd,buf,strlen(buf),0);
                }
            }
        }
        else 
        {
            //parent
            close(newsockfd);
        }
    }
    return 0;
}
