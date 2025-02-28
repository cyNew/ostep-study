#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int x = 100;
    int rc = fork();

    int pid = getpid();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process read value of x: %d\n", x);
        x = 50;
        printf("child process read value of x: %d\n", x);
    } else {
        wait(NULL);
        printf("parent process read value of x: %d\n", x);
        x = 150;
        printf("parent process read value of x: %d\n", x);
    }
    return 0;
}
