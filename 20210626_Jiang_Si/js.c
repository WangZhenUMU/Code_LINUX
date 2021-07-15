#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid=fork();
    if(pid < 0)
    {
        perror("fork:");
        return 0;
    }
    else if(pid == 0)
    {
        printf("This is child! PID:%d\n",getpid());
        sleep(3);
    }
    else 
    {
        while(1)
        {
            printf("This is parent! PID:%d\n",getpid());
            sleep(3);
        }
    }
    return 0;
}
