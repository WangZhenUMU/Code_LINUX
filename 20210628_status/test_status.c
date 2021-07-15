#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
    pid_t pid=fork();
    if(pid < 0)
    {
        perror("fork:");
        exit(1);
    }
    else if(pid == 0)
    {
        sleep(20);
        exit(10);
    }
    else 
    {
        int st;
        int ret = wait(&st);
        if(ret > 0 && (st & 0X7F) == 0)
            printf("child exit code : %d\n",(st>>8)&0xFF);
        else if(ret > 0)
        {
            printf("sig code : %d\n", st&0x7F );
        }
    }
}
