#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#define TICKET 100 // 票的总数

int ticket = TICKET;

pthread_mutex_t mutex;

void *PthreadStart(void* arg)
{
    while(true)
    {
        // 在访问临界资源之前进行加锁
        pthread_mutex_lock(&mutex);

        if(ticket > 0) // 有票
        {
            //sleep(3);
            printf("YellowOx [%d]: get a TICKET:No.%d\n",*(int*)arg,ticket--);
        }
        else // 没有票了
        {
            //加锁后需要在进程有可能退出的地方进行解锁
            pthread_mutex_unlock(&mutex); // 没有票了，在退出之前进行解锁
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex); // 抢完票后，进行解锁，让别人再去抢
    }
}

int main()
{
    pthread_t tid[2]; // 四个黄牛
    pthread_mutex_init(&mutex,NULL); // 初始化互斥锁
    int ret;
    int* a[2];
    for(int i = 0; i<2; i++)
    {
        a[i]=(int*)malloc(sizeof(int));
        *a[i]=i+1;
        ret = pthread_create(&tid[i],NULL,PthreadStart,(void*)a[i]);
        if(ret<0)
        {
            printf("YellowOx create error!");
            exit(1);
        }
    }
    for(int i=0;i<2;i++)
    {
        pthread_join(tid[i],NULL);
        free(a[i]);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
