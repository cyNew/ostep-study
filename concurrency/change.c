#include <stdlib.h>
#include <stdio.h>

typedef struct arg_t {
    int a;
    int b;
} arg_t;

void change(void *p) {
    arg_t *arg = (arg_t *)malloc(sizeof(arg_t));
    arg->a = 10;
    arg->b = 20;
    printf("function: allocate on %p\n", arg);
    // 此时 ptr 为 NULL，无法解引用
    // 即使已分配内存地址，也只是改变该内存块的值
    arg_t *ptr = p;
    *ptr = *arg;
}

void real_change(void **p ) {
    arg_t *ptr = malloc(sizeof(arg_t));
    ptr->a = 10;
    ptr->b = 20;
    printf("function: allocate on %p\n", ptr);
    *p = (void *)ptr;
}

int main() {
    arg_t *ptr = NULL;
    printf("main: allocate on: %p\n", ptr);

    // arg_t at;
    // at.a = 0;
    // at.b = 0;
    // ptr = &at;
    // change(ptr);
    real_change((void **)&ptr);

    printf("main: allocate on after changing: %p\n", ptr);
    printf("main: a: %d, b: %d\n", ptr->a, ptr->b);
    free(ptr);
    return 0;
}