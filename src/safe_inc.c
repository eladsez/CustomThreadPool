#include "safe_inc.h"
#include <pthread.h>


p_safe_inc create_safe_inc(size_t top){
    p_safe_inc si = (p_safe_inc) malloc(SAFE_INC_SIZE);
    if (si == NULL){
        perror("malloc ERROR");
        exit(1);
    }
    si->curr = -1;
    si->top = top;
    pthread_mutex_init(&si->lock, NULL);
    return si;
}

void destroy_safe_inc(p_safe_inc si){
    pthread_mutex_destroy(&si->lock);
    free(si);
}

int inc(p_safe_inc si){
    pthread_mutex_lock(&si->lock);
    if (si->curr > si->top){
        pthread_mutex_unlock(&si->lock);
        return -1;
    }
    int ret = ++si->curr;
    pthread_mutex_unlock(&si->lock);
    return ret;
}