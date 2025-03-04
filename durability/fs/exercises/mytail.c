#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEFAULT_LINES 10
#define MAX_LINE_LENGTH 1024

void print_lines(char *filename, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // 定位到文件末尾
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    long pos = file_size;
    int lines_found = 0;
    char buffer[MAX_LINE_LENGTH];

    // 从后向前读取文件内容
    while (pos) {
        fseek(file, --pos, SEEK_SET);  // 从后向前移动文件指针
        if (fgetc(file) == '\n') {
            if (lines_found++ == n) {
                break;  // 找到足够的行数
            }
        }
    }

    int lines = 0;
    // 输出最后几行
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%02d:%s", lines++, buffer);
    }
    printf("\n");

    fclose(file);
}

/**
 * usage: mytail [-n +num] file
 * `-n +num` prints last num lines, or 10 lines by default;
 */
int main(int argc, char *argv[]) {
    int n = DEFAULT_LINES;
    char *filename = argv[argc - 1];
    if (argc == 2) {
        print_lines(filename, n);
    } else if (argc == 4) {
        n = atoi(argv[argc - 2]);
        if (n == 0) {
            fprintf(stderr, "must specify lines\n");
            return EXIT_FAILURE;
        }

        print_lines(filename, n);
    } else {
        fprintf(stderr, "usage: mytail [-n +num] file");
        return EXIT_FAILURE;
    }
}