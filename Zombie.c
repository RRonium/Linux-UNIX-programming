#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    pid_t pid=fork();

    if(pid<0)
    {
        perror("Fork failure\n");
        exit(1);
    }
    else if(pid==0)
    {
        printf("Child process is now exiting. PID: %d\n",getpid()); 
        exit(0);
    }
    else
    {
        printf("Child process has been created. PID: %d\n",getpid());
        printf("Parent process is still executing. ppid: %d, pid: %d",getppid(),pid);
        sleep(30);
    }
    return 0;
}