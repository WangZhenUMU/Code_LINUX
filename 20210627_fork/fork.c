#include <stdio.h>
#include <unistd.h>

int main()
{
    int a = 10;
    int b = 20;
    pid_t pid = fork();
    if(pid < 0 )
    {
        perror("fork:");
        return 0;
    }
    else if(pid == 0)//子进程实现
    {
        printf("This is child! pid:%d ppid:%d\n",getpid(),getppid());
        a=5;
        printf("a的值为：%d, a的地址为：%p\n",a,&a);
        printf("b的值为：%d，b的地址为：%p\n",b,&b);
        sleep(3);
    }
    else//父进程实现
    {
        printf("This is parents! pid:%d ppid:%d\n",getpid(),getppid());
        
        printf("a的值为：%d, a的地址为：%p\n",a,&a);
        printf("b的值为：%d，b的地址为：%p\n",b,&b);
        sleep(3);
    }
    sleep(30);
    return 0;
}
