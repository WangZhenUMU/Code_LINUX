#include <stdio.h>
#include "sub.h"
#include "add.h"

int main()
{
    int a=10;
    int b=20;
    printf("%d + %d = %d\n",a,b,add(a,b));
    printf("%d - %d = %d\n",a,b,sub(a,b));
    return 0;
}
