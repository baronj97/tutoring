#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int i;

    for (i = 0; i < 3; i++)
    {
        printf("Parent = [%d], Child = [%d] i=%d\n", getppid(), getpid(), i);
        fork();
    }
    // printf("Parent = [%d],  Child = [%d] finished\n", getppid(), getpid());

    return 0;
}