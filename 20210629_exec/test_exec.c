#include <unistd.h>

int main()
{
    execlp("ls","ls","-l","-a",NULL);
    return 0;
}
