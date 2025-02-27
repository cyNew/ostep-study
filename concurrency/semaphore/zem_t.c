// 通过条件变量和锁实现信号量
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _Zem_t {
    int value;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} _Zem_t;

void zem_init(_Zem_t *s, int value) {
    s->value = value;
    pthread_cond_init(&s->cond, NULL);
    pthread_mutex_init(&s->lock, NULL);
}

void zem_wait(_Zem_t *s) {
    pthread_mutex_lock(&s->lock);
    // s->value--;
    // if (s->value < 0) {
    //     pthread_cond_wait(&s->cond, &s->lock);
    // }
    while (s->value <= 0) {
        pthread_cond_wait(&s->cond, &s->lock);
    }
    s->value--;

    pthread_mutex_unlock(&s->lock);
}

void zem_post(_Zem_t *s) {
    pthread_mutex_lock(&s->lock);
    // s->value++;
    // if (s->value <= 0) {
    //     pthread_cond_signal(&s->cond);
    // }
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);
}

void zem_destroy(_Zem_t *s) {
    pthread_mutex_destroy(&s->lock);
    pthread_cond_destroy(&s->cond);
    s = NULL;
}

_Zem_t zem;

int count = 0;
int loops = 100000;

void *test(void *arg) {
    int i;
    zem_wait(&zem);
    for (i = 0; i < loops; i++) {
        count++;
    }
    zem_post(&zem);
    return NULL;
}

int main(int argc, char const *argv[]) {
    zem_init(&zem, 1);
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, test, NULL);
    pthread_create(&t2, NULL, test, NULL);
    pthread_create(&t3, NULL, test, NULL);
    pthread_create(&t4, NULL, test, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("main: count %d\n", count);
    return 0;
}
