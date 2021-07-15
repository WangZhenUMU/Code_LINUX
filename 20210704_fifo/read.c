#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("./fifo",O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return 0;
    }
    char buf[1024]={0};
    read(fd,buf,1024);
    printf("%s",buf);
    return 0;
}
