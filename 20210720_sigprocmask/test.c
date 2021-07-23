#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int signo)
{
    printf("signo is %d\n",signo);
}

int main()
{
    signal(2,sigcallback);      // 当接收到二号信号时，就执行sigcallback函数。
    signal(40,sigcallback);     // 当接收到40号信号时，就执行sigcallback函数。
    sigset_t s;                 // 定义信号集对象。
    sigemptyset(&s);            // 清空信号集
    sigfillset(&s);             // 填充所有信号打到s集合中
    sigprocmask(SIG_BLOCK,&s,NULL);  // 将s集合中的信号添加到阻塞集合中
    printf("信号已经被阻塞！\n");
    getchar();
    sigprocmask(SIG_UNBLOCK,&s,NULL);// 从阻塞信号中移除s中的信号
    while(1)
        sleep(1);
    return 0;
}
