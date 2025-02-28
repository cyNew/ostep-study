#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char* args[3];
        args[0] = "/bin/ls";
        args[1] = "ls";
        args[2] = "-l";

        execlp("/bin/ls", "ls", "-l", NULL);
    } else {
        wait(NULL);
    }
    return 0;
}