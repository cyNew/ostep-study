#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = malloc(100 * sizeof(int));
    free(&data[50]);  // 无法释放非零偏移量

    return 0;
}