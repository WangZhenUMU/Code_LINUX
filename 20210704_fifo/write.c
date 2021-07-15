#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("./fifo",O_WRONLY);
    if(fd < 0)
    {
        perror("OPEN:");
        return 0;
    }
    char buf[]="I am process A!";
    write(fd,buf,sizeof(buf)-1);
    return 0;
}

