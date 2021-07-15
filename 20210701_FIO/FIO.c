#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    FILE* fp = fopen("bite","w");
    assert(fp!=NULL);
    char str[64]="Linux is so easy!";
    fwrite(str,1,sizeof(str),fp);
    fclose(fp);
    FILE* fp2 = fopen("bite","r");
    assert(fp2!= NULL);
    char buf[64];
    fread(buf,1,64,fp2);
    fclose(fp2);
    printf("%s\n",buf);
    return 0;
}
