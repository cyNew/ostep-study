#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe error");
        exit(1);
    }

    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // execlp("ls", "ls", "-l", NULL);
        fprintf(stdout, "hello from child process.\n");

        exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "for failed\n");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // execlp("wc", "wc", "-l", NULL);
        char buf[100];
        read(STDIN_FILENO, buf, sizeof(buf));

        printf("len: %d, %s", strlen(buf), buf);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
