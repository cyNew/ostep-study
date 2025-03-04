#include <assert.h>
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// 打印目录内容（只含文件）
void print_dir(char *pathname, int l_flag) {
    printf("read dir: %s\n", pathname);
    DIR *dir = opendir(pathname);
    assert(dir != NULL);

    struct dirent *d;
    struct stat s;
    char fullpath[PATH_MAX];

    if (l_flag) {
        printf("name\tuid\tgid\tsize(bytes)\tinode\n");
    }
    while ((d = readdir(dir)) != NULL) {
        if (d->d_type == DT_REG) {
            snprintf(fullpath, sizeof(fullpath), "%s/%s", pathname, d->d_name);
            if (l_flag) {
                if (stat(fullpath, &s) == 0) {
                    printf("%s\t%d\t%d\t%ld\t%ld\n", d->d_name, s.st_uid,
                           s.st_gid, (long)s.st_size, (long)s.st_ino);
                } else {
                    perror("stat");
                }
            } else {
                printf("%s\n", d->d_name);
            }
        }
    }
    closedir(dir);
}

// 获取当前工作目录
char *Get_cwd() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char *dir = malloc(strlen(cwd) + 1);
        strcpy(dir, cwd);
        return dir;
    } else {
        return NULL;
    }
}

/**
 * usage: myls [-l] [dir]
 * print all files which under specified folder.
 * `-l` will print detail of files;
 * if `dir` not specify, will open current work directory by default.
 */
int main(int argc, char *argv[]) {
    char *cwd;
    if (argc == 1) {
        if ((cwd = Get_cwd()) != NULL) {
            print_dir(cwd, 0);
        } else {
            fprintf(stderr, "open current dir failed\n");
            return EXIT_FAILURE;
        }

    } else if (argc == 2) {
        char *arg = argv[1];

        if (strcmp(arg, "-l") == 0) {
            if ((cwd = Get_cwd()) != NULL) {
                print_dir(cwd, 1);
            } else {
                fprintf(stderr, "open current dir failed\n");
                return EXIT_FAILURE;
            }
        } else {
            print_dir(arg, 0);
        }

    } else if (argc == 3) {
        char *pathname = argv[2];
        print_dir(pathname, 1);
    } else {
        fprintf(stderr, "usage: myls [-l] [dir]");
        return EXIT_FAILURE;
    }

    return 0;
}