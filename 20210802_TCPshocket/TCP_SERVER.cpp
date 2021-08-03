#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct ThreadInfo
{
    int newsockfd_;
};

void* TcpThreadStart(void* arg)
{
    pthread_detach(pthread_self());
    struct ThreadInfo* ti=(struct ThreadInfo*)arg;
    int newsockfd =  ti -> newsockfd_;
    while(1)
    {
        char buf[1024]={0};
        ssize_t recv_size =recv(newsockfd,buf,sizeof(buf)-1,0);
        if(recv_size<0)
        {
            perror("recv");
            continue;
        }
        else if(recv_size==0)
        {
            printf("peer close connect\n");
            close(newsockfd);
            break;
        }
        printf("%s\n",buf);
        strcpy(buf,"i am server!");
        send(newsockfd,buf,strlen(buf),0);
    }
    delete ti;
    return NULL;
}
int main()
{
    //创建监听套接字
    int listen_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_sock<0)
    {
        perror("sock error!");
        return 0;
    }
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
    ret = listen(listen_sock,1); //监听
    if(ret<0)
    {
        perror("listen error");
        return 0;
    }
    while(1)
    {
        struct sockaddr_in cli_addr;
        socklen_t cli_addrlen = sizeof(cli_addr);
        // 接收套接字
        int newsockfd = accept(listen_sock,(struct sockaddr*)&cli_addr,&cli_addrlen);
        if(newsockfd < 0)
        {
            perror("accept error");
            return 0;
        }
        printf("accept new connect from client %s:%d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
        struct ThreadInfo* ti = new ThreadInfo;
        ti->newsockfd_ = newsockfd;
        // 创建线程
        pthread_t tid;
        ret = pthread_create(&tid,NULL,TcpThreadStart,(void*)ti);
        if(ret<0)
        {
            close(newsockfd);
            delete ti;
            continue;
        }
    }
    close(listen_sock);
    return 0;
}
