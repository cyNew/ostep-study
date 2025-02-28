#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../common.h"

int main(int argc, char *argv[]) {
    printf("main pid: %d\n", getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        Spin(1);
    } else {
        int status;
        int pid = waitpid(rc, &status, WUNTRACED);
        printf("pid: %d, status: %d", pid, status);
        // printf("parent: wait pid: %d\n", pid);
    }

    return 0;
}
