#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct myarg_t {
    int a;
    int b;
} myarg_t;

typedef struct myret_t {
    int x;
    int y;
} myret_t;

void *mythread(void *arg) {
    myarg_t *m = (myarg_t *)arg;
    printf("%d %d\n", m->a, m->b);
    myret_t r; // assign value from thread stack
    r.x = 1;
    r.y = 2;
    return (void *)&r;
}

int main() {
    pthread_t p1;
    int rc;

    myarg_t arg;
    arg.a = 1;
    arg.b = 2;

    myret_t ret;
    pthread_create(&p1, NULL, mythread, &arg);
    pthread_join(p1, (void *)&ret);

    printf("%d %d\n", ret.x, ret.y);

    return 0;
}