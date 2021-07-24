#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int signo)
{
    printf("siggno:%d\n",signo);
}

int main()
{
    signal(2,sigcallback);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
