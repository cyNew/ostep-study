#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread(void *arg) {
    pthread_mutex_lock(&lock);

    for (int i = 0; i < *(int *)arg; i++) {
        counter = counter + 1;
    }

    int *result = (int *)malloc(sizeof(int));
    *result = counter;

    pthread_mutex_unlock(&lock);
    return (void *)result;
}

int main() {
    pthread_t p1, p2;
    int i1 = 1000;
    int i2 = 2000;
    pthread_create(&p1, NULL, mythread, (void *)&i1);
    pthread_create(&p2, NULL, mythread, (void *)&i2);

    int *p1_ret = NULL;
    int *p2_ret = NULL;

    printf("main: p1_ret: %p\n", &p1_ret);
    printf("main: p2_ret: %p\n", &p2_ret);

    pthread_join(p1, (void **)&p1_ret);
    pthread_join(p2, (void **)&p2_ret);

    assert(counter == 3000);

    printf("main counter: %d\n", counter);
    printf("p1 returned value: %d\n", p1_ret);
    printf("p2 returned value: %d\n", p2_ret);

    printf("main: p1_ret: %p\n", &p1_ret);
    printf("main: p2_ret: %p\n", &p2_ret);


    return 0;
}