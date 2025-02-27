#include <semaphore.h>

typedef struct _rwlock_t {
    sem_t lock;        // binary lock
    sem_t write_lock;  // used to allow ONE writer or many readers
    int readers;       // count of readers reading in critical section
} _rwlock_t;

// rwlock 初始化
void rwlock_init(_rwlock_t *rw) {
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->write_lock, 0, 1);
    rw->readers = 0;
}

void rwlock_acquire_readlock(_rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1) {
        sem_wait(&rw->write_lock);
    }
    sem_post(&rw->lock);
}

void rwlock_release_readlock(_rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0) {
        sem_post(&rw->write_lock);
    }
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(_rwlock_t *rw) {
    sem_wait(&rw->write_lock);
}

void rwlock_release_writelock(_rwlock_t *rw) {
    sem_post(&rw->write_lock);
}