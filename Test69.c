#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        printf("Process creation failure!\n");
        exit(1);
    }
    else if(pid==0)         //For the child process
    {
        printf("Child process ahs been created successfully. Running now...PID: %d",getpid());
        sleep(10);
        printf("Child process done executing, terminanting now...PID: %d| Parent PID: %d",getpid(),getppid());
        exit(0);
    }
    else                    //For the parent process
    {
        printf("Parent process is executing...PID: %d",getpid());
        sleep(50);
    }
    return 0;
}