#include "thread_pool.h"
#include <stdlib.h>

#define MAX_THREADS 10000
#define THREAD_STACK  65536



p_thread_pool create_pool(void* (func)(void *), p_safe_inc si){
    p_thread_pool pool = (p_thread_pool) malloc(TH_POOL_SIZE);
    if (pool == NULL){
        perror("malloc ERROR");
        exit(1);
    }
    pool->si = si;
    pool->func = func;
    pool->threads = (pthread_t *) malloc(sizeof(pthread_t) * MAX_THREADS);
    if (pool->threads == NULL){
        perror("malloc ERROR");
        exit(1);
    } // TODO: add support for saving the threads in a smarter way
    return pool;
}

void destroy_pool(p_thread_pool pool){
    free(pool->threads); // TODO: add support for saving the threads in a smarter way
    free(pool);
}

void start_pool(p_thread_pool pool){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, THREAD_STACK);
//    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // TODO: check if needed
    int i, curr;
    for (i = 0; i < pool->threads_amount; ++i) {
        curr = inc(pool->si);
        args arg = {pool->si, curr};
        if (curr != -1)
            pthread_create(&pool->threads[i], &attr, pool->func, &arg);
        else
            break;
    }
    for (int j = 0; j < i; ++j) {
        pthread_join(pool->threads[j], NULL);
    }
}