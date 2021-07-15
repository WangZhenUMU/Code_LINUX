#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork:");
        exit(0);
    }
    if(pid == 0)// 子进程 
    {
        printf("I am child process! pid : %d\n",getpid());
        sleep(5);
        exit(1);
    }
    else  
    {
        int status = 0;
        pid_t ret = 0;
        do
        {
            ret = waitpid(-1,&status,WNOHANG);
            if(ret == 0)
            {
                printf("child is running\n");
            }
            sleep(1);
        }while(ret == 0);
        if(WIFEXITED(status) && ret == pid)
        {
            printf("wait child success,child return code is : %d\n",WIFEXITED(status));
        }
        else 
        {
            printf("wait child fild,return!\n");
            exit(1);
        }
    }
    return 0;
}
