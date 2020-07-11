#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child;

    child = fork();

    if (child == 0){
        printf("CHILD (%u): Running\n", getpid());
        sleep(5);
        printf("CHILD (%u): Exiting\n", getpid());
    } else if (child != -1) {
        printf("PARENT (%u): Waiting for child to finish\n", getpid());
        wait(NULL);
        printf("PARENT(%u): Exiting\n", getpid());
    } else {
        printf("PARENT(%u): Not enough resources to fork!\n", getpid());
    }

    return 0;
}