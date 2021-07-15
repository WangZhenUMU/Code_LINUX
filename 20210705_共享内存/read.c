#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define IPC_F 0X66666666

int main()
{
    //创建共享内存
    int shmid = shmget(IPC_F,1024,IPC_CREAT | 0664);
    if(shmid < 0)
    {
        perror("shmget:");
        return 0;
    }
    //将共享内存链接到进程地址空间
    void* addr = shmat(shmid,NULL,SHM_RDONLY);
    if(addr == NULL)
    {
        perror("shmat:");
        return 0;
    }
    while(1)
    {
        printf("%s",(char*)addr);
        sleep(2);
    }
    shmctl(shmid,IPC_RMID,NULL);
    //IPC_RMID 删除共享内存段
    //IPC_STAT 把shmid_ds结构中的数据设置成为共享内存中的关联值
    //IPC_SET  在进程有足够的权限下，把共享内存中的关联值设置为shmid_ds结构中给出的值
    return 0;
}

