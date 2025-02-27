#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct queue_t {
} queue_t;

void queue_init(queue_t *q) {
}

typedef struct lock_t {
    int flag;
    int guard;
    queue_t *q;
} lock_t;

void *mythread(void *arg) {
    return NULL;
}

int main() {
    printf("Hello world!\n");
    pthread_t p;
    pthread_create(&p, NULL, mythread, NULL);
    pthread_join(p, NULL);
    return 0;
}
