#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define IPC_F 0X66666666

int main()
{
    int shmid =shmget(IPC_F,1024,IPC_CREAT | 0644);
    if(shmid < 0)
    {
        perror("shmget:");
        return 0;
    }
    void* addr =shmat(shmid,NULL,0);
    if(addr == NULL)
    {
        perror("shmat:");
        return 0;
    }
    int count = 0;
    while(1)
    {
        char lp[1024] = "I am process A!\n";
        sprintf(lp,"%s-%d",lp,count++);
        strncpy((char*)addr,lp,1024);
        sleep(2);
    }
    return 0;
}
