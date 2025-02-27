/**
 * 问题描述：打开文件，子进程和父进程可以同时访问该文件描述符吗？
 *         如果同时写入文件呢？
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_s_ifmt.h>
#include <unistd.h>

int main() {
    int fd = open("./ex2.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child read file descriptor: %d\n", fd);
        char* text = "Greetings from child\n";
        write(fd, text, strlen(text));
    } else {
        printf("parent read file descriptor: %d\n", fd);
        char* text = "Greetings from parent\n";
        write(fd, text, strlen(text));
    }

    return 0;
}
