#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 10

int buffer[MAX];
int fill = 0;
int use = 0;

sem_t mutex;

void put(int value) {
    sem_wait(&mutex);
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
    sem_post(&mutex);
}

int get() {
    sem_wait(&mutex);
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    sem_post(&mutex);
    return tmp;
}

sem_t empty;
sem_t full;
int loops = 100;

void *producer(void *arg) {
    char *name = (char *)arg;
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&empty);
        put(i);
        sem_post(&full);
        printf("%s produced: %d\n", name, i);
    }
    return NULL;
}

void *consumer(void *arg) {
    char *name = (char *)arg;
    int i, tmp = 0;
    for (i = 0; i < loops; i++) {
        sem_wait(&full);
        tmp = get();
        sem_post(&empty);
        printf("%s consumed: %d\n", name, tmp);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t p1, p2, c1, c2, c3;
    pthread_create(&p1, NULL, producer, "producer-1");
    pthread_create(&p2, NULL, producer, "producer-2");
    pthread_create(&c1, NULL, consumer, "consumer-1");
    pthread_create(&c2, NULL, consumer, "consumer-2");
    pthread_create(&c3, NULL, consumer, "consumer-3");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    pthread_join(c3, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sleep(5);

    return 0;
}
