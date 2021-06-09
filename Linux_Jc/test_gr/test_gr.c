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
        while(1)
        {
           printf("I'm subprocess,this is my pid %d ,this is my ppid %d .\n",getpid(),getppid());
           sleep(2);
        }
    }
    else 
    {    
        printf("I'm fatherprocess,this is my pid %d ,this is my ppid %d .\n",getpid(),getppid());
    }
    return 0;
}
