/**
 * 使用 fork 新增子进程，在父进程不使用 wait 函数的情况下，
 * 子进程先打印 “hello”，父进程再打印 “goodbye”。
 * 确保子进程始终先打印
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;

    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        close(pipefd[0]); // 关闭读端
        printf("child: hello\n");
        close(pipefd[1]); // 关闭写端
    } else {
        close(pipefd[1]); // 关闭写端
        char buf;
        while (read(pipefd[0], &buf, 1)) {
            // 读取读端
        }
        printf("parent: goodbye\n");
        close(pipefd[0]); // 关闭读端
    }
    return 0;
}
