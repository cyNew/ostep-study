#include <pthread.h>

#ifndef PTHREAD_H
#define PTHREAD_H

typedef void *(*task)(void *);

int Pthread_create(pthread_t *, pthread_attr_t *, task, void *);

int Pthread_join(pthread_t th, void **ret_val);

#endif