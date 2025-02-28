#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../common.h"

int main(int argc, char* argv[]) {
    printf("main pid: %d\n", getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        wait(NULL);
        printf("child: pid: %d\n", getpid());
        printf("child rc: %d\n", rc);
    } else {
        // int pid = wait(NULL);
        printf("parent: rc: %d\n", rc);
        printf("parent: getpid(): %d\n", getpid());
        // printf("parent: wait pid: %d\n", pid);
    }

    return 0;
}
