#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void mycallback(void)
{
    printf("I am mycallback \n");
}
int main()
{
    atexit(mycallback);
    printf("hello atexit\n");
    return 0;
}
