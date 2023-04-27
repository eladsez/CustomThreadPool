#ifndef DESIGN_PATTERNS_ACTIVE_OBJECT_H
#define DESIGN_PATTERNS_ACTIVE_OBJECT_H

#include "safe_inc.h"

#define MAX_THREADS 1000
#define THREAD_STACK  65536

#define TH_POOL_SIZE sizeof(struct thread_pool_t)

struct args{
    p_safe_inc si;
    int init_val;
};
typedef struct args args;

struct thread_pool_t {
    size_t threads_amount;
    pthread_t *threads;
    p_safe_inc si;
    void* (*func)(void *);
};

typedef struct thread_pool_t *p_thread_pool;

p_thread_pool create_pool(void* (func)(void *), p_safe_inc si);

void destroy_pool(p_thread_pool pool);

void start_pool(p_thread_pool pool);


#endif //DESIGN_PATTERNS_ACTIVE_OBJECT_H
