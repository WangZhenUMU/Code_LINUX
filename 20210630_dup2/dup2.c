#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
    int fd = open("text",O_WRONLY | O_CREAT,0644);
    if(fd<0)// 打开失败
    {
        perror("open:");
        return 1;
    }
    close(1);
    dup2(fd,1);
    while(1)
    {
        char buf[1024]={0};
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size<0)
        {
            perror("read:");
            break;
        }
        printf("%s",buf);
        fflush(stdout);
    }
    return 0;
}
