#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        printf("Faliure!\n");
        exit(1);
    }
    else if(pid==0)
    {
        printf("Child process has been created and is running. PID:%d",getpid());
        sleep(10);
        printf("Child process finished running, now terminating. PID: %d | Parent PID: %d\n",getpid(),getppid());
        exit(0);
    }
    else
    {
        printf("Parent is executing and is goint to wait for the child process to execute and then terminate. Parent PID:%d\n",getpid());
        wait(NULL);
    }
    return 0;
}