#include "thread_pool.h"
#include <stdlib.h>

p_thread_pool create_pool(void* (func)(void *), p_safe_inc si){
    p_thread_pool pool = (p_thread_pool) malloc(TH_POOL_SIZE);
    if (pool == NULL){
        perror("malloc ERROR");
        exit(1);
    }
    pool->si = si;
    pool->func = func;
    pool->threads_amount = MAX_THREADS;
    pool->threads = (pthread_t *) malloc(sizeof(pthread_t) * pool->threads_amount);
    if (pool->threads == NULL){
        perror("malloc ERROR");
        exit(1);
    } // TODO: add support for saving the threads in a smarter way
    return pool;
}

void destroy_pool(p_thread_pool pool){
    // killing all the threads
    free(pool->threads); // TODO: add support for saving the threads in a smarter way
    free(pool);
}

void start_pool(p_thread_pool pool){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, THREAD_STACK);
//    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // TODO: check if needed
    args *arg = (args *) malloc(sizeof(args) * pool->threads_amount);
    int i;
    for (i = 0; i < pool->threads_amount; ++i) {
        arg[i].init_val = inc(pool->si);
        arg[i].si = pool->si;
        if (arg[i].init_val != -1)
            pthread_create(&pool->threads[i], &attr, pool->func, arg + i);
        else
            break;
    }
    for (int j = 0; j < i; ++j) {
        pthread_join(pool->threads[j], NULL);
    }
    free(arg);
    pthread_attr_destroy(&attr);
}