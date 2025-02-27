#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    assert(fd > -1);

    char *text = "hello world\n";
    int rc = write(fd, text, strlen(text));
    assert(rc == strlen(text));
    close(fd);
    return 0;
}
