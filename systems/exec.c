#include <stdio.h>
#include <unistd.h>

int main() {
    /* execl and execlp use a listing of argumenets */
    char *path = "/bin/ls";
    char *arg1 = "-la";
    char *arg2 = "/usr/lib";

    /* Notice, execl does not use PATH */
    execl(path, path, arg1, arg2, NULL);
 
    char *prog = "ls";
    execlp(prog, prog, arg1, arg2, NULL);

    /* execv and exexcp use a variadic array */
    char *args[] = {path, "-la", "/usr/lib", NULL};
    execv(path, args);

    execvp(prog, args);
    return 0;
}