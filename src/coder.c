#include "../build/codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thread_pool.h"

#define MAX_SIZE 1024 * 1024 // 1MB
#define CHUNK_SIZE 1024

#define WRAP(curr) (e_d ? encrypt(global_data + curr * CHUNK_SIZE, global_key) : decrypt(global_data + curr * CHUNK_SIZE, global_key))

char *global_data;
int global_key;
char e_d;

void *wrap_crypt(void *p) {
    args *arg = (args *) p;
    WRAP(arg->init_val);
    while (inc(arg->si) != -1) {
        WRAP(arg->si->curr);
    }
    return NULL;
}

void print_usage() {
    printf("Usage: ./Coder key [-e | -d] < input_file\n"
           "       ./Coder key [-e | -d] < input_file > _output_file\n"
           "       cat output_file | ./Coder key [-e | -d] > output_file\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage();
        return 0;
    }

    int key = atoi(argv[1]);

    char c;
    int counter = 0;
    char data[MAX_SIZE];
    bzero(data, MAX_SIZE);

    while ((c = getchar()) != EOF)
        data[counter++] = c;

    size_t chunks_amount = counter / CHUNK_SIZE;

    global_data = data; // its never get segfault because the data local stacked in the main and if its get free the program finished
    global_key = key;

    if (!strcmp(argv[2], "-e")) {
        /* TODO: Add logic to split every 1024 chars and process with threadpool */
        e_d = 1;
    } else if (!strcmp(argv[2], "-d")) {
        /* TODO: Add logic to split every 1024 chars and process with threadpool */
        e_d = 0;
    } else {
        print_usage();
        return 1;
    }

    p_safe_inc si = create_safe_inc(chunks_amount);
    p_thread_pool pool = create_pool(wrap_crypt, si);
    start_pool(pool);
    destroy_pool(pool);
    destroy_safe_inc(si);

    printf("%s", data);
    return 0;
}