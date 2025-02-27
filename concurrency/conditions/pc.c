// producer and consumers
#include <assert.h>
#include <pthread.h>
#include <stdio.h>

#define MAX 10

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}

pthread_cond_t empty, fill;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int i;
    int *loops = (int *)arg;
    for (i = 0; i < *loops; i++) {
        pthread_mutex_lock(&mutex);             // p1
        while (count == MAX) {                  // p2
            pthread_cond_wait(&empty, &mutex);  // p3
        }
        put(i);                        // p4
        pthread_cond_signal(&fill);    // p5
        pthread_mutex_unlock(&mutex);  // p6
    }
    return NULL;
}

void *consumer(void *arg) {
    pthread_t *t = (pthread_t *)arg;
    int i;
    while (1) {
        pthread_mutex_lock(&mutex);            // c1
        while (count == 0) {                   // c2
            pthread_cond_wait(&fill, &mutex);  // c3
        }
        int tmp = get();              // c4
        pthread_cond_signal(&empty);  // c5
        pthread_mutex_unlock(&mutex);
        printf("%ld: %d\n", *t, tmp);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    int loops = 100;

    pthread_t p1, p2, p3;

    pthread_create(&p1, NULL, producer, &loops);
    pthread_create(&p2, NULL, consumer, &p2);
    pthread_create(&p3, NULL, consumer, &p3);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    return 0;
}
