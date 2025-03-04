#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * 指定文件或目录，输出 inode，文件大小，分配块数，引用数
 */
int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "must specify a file or dir path\n");
        return EXIT_FAILURE;
    }

    char const *pathname = argv[1];
    struct stat s;
    stat(pathname, &s);

    printf("name\tinode\tsize(bytes)\tdisk_blk\tlinks\n");
    printf("%s\t%lu\t%d\t%d\t%d\n", pathname, s.st_ino, s.st_size, s.st_blocks,
           s.st_nlink);
    return 0;
}