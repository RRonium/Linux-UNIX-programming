#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t pid=fork();

    if(pid<0)
    {
        printf("Thread Creation Failure!\n");
        exit(1);
    }
    if(pid==0)
    {
        printf("Child process has just started. Child pid: %d, Parent pid: %d\n",getpid(),getppid());
        sleep(10);
        printf("Child process still running. PID: %d, Parent PID: %d\n",getpid(),getppid());
        exit(0);
    }
    else
    {
        printf("Parent process is terminating PID: %d\n",getpid());
        exit(NULL);
    }
    return 0;
}