#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe:");
        return 0;
    }
    printf("fd[0] : %d\nfd[1] : %d\n",fd[0],fd[1]);
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork:");
        return 0;
    }
    else if(pid == 0)
    {
        // 子进程
        close(fd[1]);
        char buff[1024]={0};
        read(fd[0],buff,sizeof(buff)-1);
        printf("child read : %s\n",buff);
    }
    else 
    {
        // 父进程
        close(fd[0]);
        char buf[1024]="I am father!";
        write(fd[1],buf,strlen(buf));
    }
    return 0;
}
