#include <stdlib.h>

int main() {
    int *mem = malloc(sizeof(int));

    *mem = 10;

    return 0;
}