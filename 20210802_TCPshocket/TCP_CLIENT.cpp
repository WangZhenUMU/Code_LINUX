#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// 客户端
// 创建网络套接字
// 定义sockaddr_in对象，用来存储服务器端口信息
// 向服务端请求链接
// 向服务端发送数据/从服务端获取数据
int main()
{
    // 创建网络套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0)
    {
        perror("socket error");
        return 0;
    }
    // 定义sockaddr_in对象
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10086);
    addr.sin_addr.s_addr=inet_addr("172.21.0.6");
    // 向服务端请求连接
    int ret = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("connect error!");
        return 0;
    }
    while(1)
    {
        char buf[1024]="client";
        send(sockfd,buf,strlen(buf)-1,0);
        memset(buf,'\0',sizeof(buf));
        ssize_t recv_size = recv(sockfd,buf,sizeof(buf)-1,0);
        if(recv_size < 0)
        {
            perror("recv");
            continue;
        }
        else if(recv_size == 0)
        {
            printf("peer close connect\n");
            close(sockfd);
            continue;
        }
        printf("%s\n",buf);
        sleep(1);
    }
    close(sockfd);
    return 0;
}
