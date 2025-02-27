#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("Hello world (pid: %d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Hello, I am child (pid: %d)\n", (int)getpid());
        char* myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p3.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("this shouldn't print out");  // not print
    } else {
        int wc = wait(NULL);
        printf("Hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc,
               (int)getpid());
    }
    return 0;
}