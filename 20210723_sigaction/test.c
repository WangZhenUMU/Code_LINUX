#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction oldact;

void sigcb(int signo)
{
    printf("I'm sigcb,my signomeber is %d \n",signo);
    sigaction(SIGINT,&oldact,NULL);
}
int main()
{
    struct sigaction act;
    act.sa_handler = sigcb;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT,&act,&oldact);
    while(1)
        sleep(1);
    return 0;
}

