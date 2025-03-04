#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char* text = "Hello world";
    char* filename = "./test.txt";
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
    int bytes = write(fd, text, strlen(text));
    printf("write %d bytes\n", bytes);

    // 会读取当前进程打开的文件所在的偏移量
    int offset = lseek(fd, 0, SEEK_CUR);
    assert(offset == bytes);
    printf("existed file offset: %d\n", offset);

    // remove(filename);
    // unlink(filename);
    return 0;
}