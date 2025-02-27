#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

void *thread_function(void *arg) {
    counter_t *counter = (counter_t *)arg;

    for (int i = 0; i < 1000000; i++) {
        increment(counter);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    printf("arguments count: %d\n", argc);
    int thread_count = atoi(argv[1]);
    printf("threads count: %d\n", thread_count);

    counter_t counter;
    init(&counter);

    pthread_t threads[thread_count];

    for (int i = 0; i < thread_count; i++) {
        int rc = pthread_create(&threads[i], NULL, thread_function,
                                (void *)&counter);
        assert(rc == 0);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("counter: %d\n", counter.value);

    return 0;
}
