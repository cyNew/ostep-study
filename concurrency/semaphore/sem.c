#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t t;

void *child(void *) {
    printf("child\n");
    sem_post(&t);
    return NULL;
}

int main(int argc, char *argv[]) {
    sem_init(&t, 0, 0);
    printf("parent: begin\n");
    pthread_t c;

    pthread_create(&c, NULL, child, NULL);

    sem_wait(&t);
    printf("parent: end\n");
    return 0;
}
