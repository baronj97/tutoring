#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int first_pipe_fds[2];  /* Maintain an array of 2 integers to maintain the file descriptors for the first pipe */
    int second_pipe_fds[2]; /* Maintain an array of 2 integers to maintain the file descriptors for the second pipe */

    char foo[] = "foo";  /* String the parent process will send to the child for concatenation*/
    char bar[] = "-bar"; /* String the child process will concatenate to the foo */

    pid_t pid; /* process ID of child */

    /* pipe() returns -1 if it wasn't possible to create a pipe */
    if (pipe(first_pipe_fds) == -1)
    {
        fprintf(stderr, "piping failure");
        return 1;
    }

    /* pipe() returns -1 if it wasn't possible to create a pipe */
    if (pipe(second_pipe_fds) == -1)
    {
        fprintf(stderr, "piping failure");
        return 1;
    }

    pid = fork(); /* Create the child process*/

    if (pid < 0) /* If fork() returns a negative number, then the forking failed */
    {
        fprintf(stderr, "forking failure");
        return 1;
    }
    else if (pid > 0) /* When pid is positive, then this is the parent */
    {
        char new_str[100]; /* Allocate a string of size 100 characters */

        close(first_pipe_fds[0]);                       /* Close the reading end of the first pipe */
        write(first_pipe_fds[1], foo, strlen(foo) + 1); /* Write foo to the writing end of the first pipe */
        close(first_pipe_fds[1]);                       /* Close the writing end of the first pipe to signal it is ready to be read from */

        wait(NULL);                /* Wait onn the child process to do its work */
        close(second_pipe_fds[1]); /* Close the writing end of the second pipe */

        read(second_pipe_fds[0], new_str, 100); /* Read from the reading end of the second pipe and grab the new string */
        printf("new string = %s\n", new_str);   /* Print the new string */
        close(second_pipe_fds[0]);              /* Close the reading end of the second pipe */
    }
    else /* Pid must be 0 if we got here, meaning it is the child */
    {
        close(first_pipe_fds[1]); /* Close the writing end of the first pipe */

        char new_str[100];                     /* Allocate a string of size 100 characters */
        read(first_pipe_fds[0], new_str, 100); /* Read from the first pipe */

        /* Next few lines are string concatenation (could have also used strcat() */
        int k = strlen(new_str); /* Obtain the length of the new string (which would put us at the end of foo) */
        int i;
        for (i = 0; i < strlen(bar); i++)
        {
            new_str[k++] = bar[i]; /* Beginning concatenating "-bar" to the end of "foo" */
        }

        new_str[k] = '\0'; /* Strings in C require a NULL terminator to signal the end of the string */

        close(first_pipe_fds[0]);  /* Close the reading end of the first pipe */
        close(second_pipe_fds[0]); /* Close the reading end of the second pipe */

        write(second_pipe_fds[1], new_str, strlen(new_str) + 1); /* Write the new, concatenated string back to the writing end of the second pipe */
        close(second_pipe_fds[1]);                               /* Close the writing end of the second pipe */
        exit(0);                                                 /* End the child process */
    }

    return 0;
}