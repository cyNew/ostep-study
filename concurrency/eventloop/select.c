#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void processFD(int fd) {
    printf("read fd: %d\n", fd);
}

int minFD = 0;
int maxFD = FD_SETSIZE;

int main(void) {
    while (1) {
        // initialize the fd_set to all zero
        fd_set readFDs;
        FD_ZERO(&readFDs);

        // now set the bits for descriptor
        // this server is interested in
        // for simplicity, all of them from min to max
        int fd;
        for (fd = minFD; fd < maxFD; fd++) {
            FD_SET(fd, &readFDs);
        }

        int rc = select(maxFD + 1, &readFDs, NULL, NULL, NULL);
        // check which actually have data using FD_ISSET()
        for (fd = minFD; fd < maxFD; fd++) {
            if (FD_ISSET(fd, &readFDs)) {
                processFD(fd);
            }
        }
    }
}