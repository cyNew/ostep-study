#include "pthread.h"

#include <assert.h>

int Pthread_create(pthread_t *th, pthread_attr_t *attr, task t, void *arg) {
    int rc = pthread_create(th, attr, t, arg);
    assert(rc == 0);
    return rc;
}

int Pthread_join(pthread_t th, void **ret_val) {
    int rc = pthread_join(th, ret_val);
    assert(rc == 0);
    return rc;
}