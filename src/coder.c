#include "../build/codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thread_pool.h"

#define MAX_SIZE 1024 * 1024 // 1MB
#define MAX_CHUNK_SIZE 1024

#define WRAP(data) (e_d ? encrypt(data, global_key) : decrypt(data, global_key))

char *global_data;
int global_key;
char e_d;
int chunk_size = MAX_CHUNK_SIZE;

void *wrap_crypt(void *p) {

    char curr_data[chunk_size + 1];
    args *arg = (args *) p;

    strncpy(curr_data, global_data + arg->init_val * chunk_size, chunk_size);
    curr_data[chunk_size] = '\0';
    WRAP(curr_data);
    strncpy(global_data + arg->init_val * chunk_size, curr_data, chunk_size);

    int curr;
    while ((curr = inc(arg->si)) != -1) {
        strncpy(curr_data, global_data + curr * chunk_size, chunk_size);
        curr_data[chunk_size] = '\0';
        WRAP(curr_data);
        strncpy(global_data + curr * chunk_size, curr_data, chunk_size);
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

    if (!strcmp(argv[2], "-e")) {
        e_d = 1;
    } else if (!strcmp(argv[2], "-d")) {
        e_d = 0;
    } else {
        print_usage();
        return 1;
    }

    char c;
    int counter = 0;
    char data[MAX_SIZE];
    bzero(data, MAX_SIZE);

    while ((c = getchar()) != EOF)
        data[counter++] = c;

    if (counter < 1){
        printf("Error: input file is empty\n");
        return 1;
    }

    chunk_size = counter / MAX_THREADS;
    if (chunk_size > MAX_CHUNK_SIZE) {
        chunk_size = MAX_CHUNK_SIZE;
    }

    size_t chunks_amount = counter / chunk_size;

    global_data = data; // its never get segfault because the data local stacked in the main and if its get free the program finished
    global_key = key;

    p_safe_inc si = create_safe_inc(chunks_amount);
    p_thread_pool pool = create_pool(wrap_crypt, si);
    start_pool(pool);
    destroy_pool(pool);
    destroy_safe_inc(si);

    for (int i = 0; i < counter; ++i) {
        printf("%c", data[i]);
    }
    return 0;
}