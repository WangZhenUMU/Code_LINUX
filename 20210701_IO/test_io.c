#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
    int fd = open("bite",O_RDWR | O_CREAT,0664);
    if(fd < 0)
    {
        perror("open:");
        exit(0);
    }
    char buf[]="I like linux!";
    int wr = write(fd,buf,sizeof(buf));
    if(wr < 0)
    {
        perror("write:");
        exit(0);
    }
    close(fd);
    int fd2 = open("bite",O_RDONLY | O_CREAT,0664);
    char buf2[1024];
    read(fd2,buf2,256);
    close(fd);
    printf("buf2:%s\n",buf2);
    return 0;
}
