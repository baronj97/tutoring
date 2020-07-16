#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Signal handler to catch various signals and print out its information */
void signal_handler(int sig)
{
    printf("Caught signal %d = %s\n", sig, sys_signame[sig]); /* sys_signame is an array that returns the signal's name */
}

int main()
{
    signal(SIGINT, signal_handler); /* Register the signal (SIGINT) to the signal handler */
    while (1)                       /* Loop forever */
    {
        printf("Hello, world!\n");
        sleep(1);
    }
}