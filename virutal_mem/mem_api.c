#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void func() {
    int *x = (int *)malloc(sizeof(int));
    free(x);
}

int main(int argc, char *argv[]) {
    int *x = malloc(10 * sizeof(int));
    char *src = "hello";
    char *dst = malloc(strlen(src) + 1);
    strcpy(dst, src);

    printf("%s, %d\n", dst, strlen(dst));
    free(dst);
    return 0;
}
