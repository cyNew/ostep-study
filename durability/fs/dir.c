#include <assert.h>
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // open and read folder
    char buf[PATH_MAX];
    char *dir = getcwd(buf, sizeof(buf));

    DIR *dp = opendir(dir);
    assert(dp != NULL);
    struct dirent *d;
    while ((d = readdir(dp)) != NULL) {
        printf("%d %s\n", (int)d->d_ino, d->d_name);
    }

    return 0;
}