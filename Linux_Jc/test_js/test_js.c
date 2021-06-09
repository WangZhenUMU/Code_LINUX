#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork error!\n");
        return 0;
    }
    else if(0 == pid)
    {
        printf("I'm subprocess,this is my pid %d ,this is my ppid %d .\n",getpid(),getppid());
    }
    else 
    {   
        while(1)
        {
            printf("I'm fatherprocess,this is my pid %d ,this is my ppid %d .\n",getpid(),getppid());
            sleep(1);

        }
    }
    return 0;
}
