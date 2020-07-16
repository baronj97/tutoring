#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig)
{
    printf("Caught signal %d = %s\n", sig, sys_signame[sig]);
}

int main()
{
    signal(SIGINT, signal_handler);
    while (1)
    {
        printf("Hello, world!\n");
        sleep(1);
    }
}