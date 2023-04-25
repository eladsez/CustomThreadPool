/**
 * This file represent the header of our implementation to safe-thread queue with mutex and condition variable
 * using pthread_cond and pthread_mutex
 */

#ifndef SAFE_INC_H
#define SAFE_INC_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SAFE_INC_SIZE sizeof(struct safe_inc)

struct safe_inc {
    int curr;
    int top;
    pthread_mutex_t lock;
};
typedef struct safe_inc* p_safe_inc;

p_safe_inc create_safe_inc(size_t top);

void destroy_safe_inc(p_safe_inc si);

int inc(p_safe_inc si); // return the curr if the inc was successful, -1 otherwise

#endif //SAFE_INC_H
