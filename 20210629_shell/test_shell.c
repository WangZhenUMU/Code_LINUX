#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_CMD 1024
char command[MAX_CMD];

int do_face()
{
    memset(command,0X00,MAX_CMD);
    printf("myshell$");
    fflush(stdout);
    if(scanf("%[^\n]%*c",command)==0)
    //  scanf("%[^\n]%*c",command)表示读入一行字符串。
    //  ^表示"非"，[^\n]表示读入换行字符就结束读入。
    //  *表示该输入项读入后不赋予任何变量，即scanf("%*[^\n]%*c",command)表示跳过一行字符串
    {
        getchar();
        return -1;
    }
    return 0;
}
char **do_parse(char *buff)
{
    int argc = 0;
    static char* argv[32];
    char* ptr = buff;
    while(*ptr != '\0')
    {
        if(!isspace(*ptr))
        {
            argv[argc++] = ptr;
            while((!isspace(*ptr)) && (*ptr!='\0'))
            {
                ptr++;
            }
        }
        else 
        {
            while(isspace(*ptr))
            {
                *ptr = '\0';
                ptr++;
            }
        }
    }
    argv[argc]=NULL;
    return argv;
}

int do_exec(char *buff)
{
    char **argv ={NULL};
    int pid = fork();
    if(pid == 0)
    {
        argv =do_parse(buff);
        if(argv[0] == NULL)
        {
            exit(0);
        }
        execvp(argv[0],argv);
    }
    else 
    {
        waitpid(pid,NULL,0);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    while(1)
    {
        if(do_face()<0)
            continue;
        do_exec(command);
    }
    return 0;
}
