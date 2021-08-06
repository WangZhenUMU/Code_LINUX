#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0)
    {
        perror("socket");
        return 0;
    }
    printf("socket : %d\n",sockfd);
    while(1)
    {
        char buf[1024] = " i am client";
        struct sockaddr_in dest_addr;
        dest_addr.sin_family=AF_INET;
        dest_addr.sin_port = htons(10086);
        dest_addr.sin_addr.s_addr = inet_addr("172.21.0.6");
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&dest_addr,sizeof(dest_addr));
        memset(buf,'\0',sizeof(buf));
        struct sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        ssize_t recv_size = recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer_addr,&len);
        if(recv_size < 0)
        {
            continue;
        }
        printf("recv msg %s from %s:%d\n",buf,inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
        sleep(1);
    }
    close(sockfd);
    return 0;
}
