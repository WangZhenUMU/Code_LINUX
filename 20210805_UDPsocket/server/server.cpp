#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd < 0)
    {
        perror("socket");
        return 0;
    }
    printf("socket : %d\n" ,sockfd);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10086);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind error!");
        return 0;
    }
    while(1)
    {
        char buf[1024] = {0};
        struct sockaddr_in peer_addr;
        socklen_t len =sizeof(peer_addr);
        ssize_t recv_size = recvfrom(sockfd, buf , sizeof(buf)-1, 0, (struct sockaddr*)&peer_addr,&len);
        if(recv_size<0)
        {
            continue;
        }
        printf("recv msg \"%s\" from %s:%d\n",buf,inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
        memset(buf ,'\0',sizeof(buf));
        sprintf(buf,"while client %s:%d" , inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"welcome client %s:%d",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&peer_addr,sizeof(peer_addr));
    }
    close(sockfd);
    return 0;
}
