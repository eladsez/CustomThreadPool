

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../build/codec.h"

#define MAX_SIZE 1024 * 1024 // 1MB
#define CHUNK_SIZE 1024


/**
 * main to encrypt and decrypt the data with the key in a serial way (without threads) every 1024 chars
 * and print the result to stdout
 * @return nothing
 */
int main(int argc, char *argv[]){

    if (argc != 3){
        printf("Usage: ./Coder key [-e | -d] < input_file\n"
               "       ./Coder key [-e | -d] < input_file > _output_file\n"
               "       cat output_file | ./Coder key [-e | -d] > output_file\n");
        return 0;
    }

    // get key and -d or -e from argv
    int key = atoi(argv[1]);
    char e_d;
    if (strncmp(argv[2], "-e", 2) == 0){
        e_d = 1;
    } else if (strncmp(argv[2], "-d", 2) == 0){
        e_d = 0;
    } else {
        printf("Error: invalid argument second for [-e | -d]\n");
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

    size_t chunks_amount = counter / CHUNK_SIZE;

    if (e_d) {
        for (int i = 0; i <= chunks_amount; ++i) {
            encrypt(data + i * CHUNK_SIZE, key);
        }
    }
    else {
        for (int i = 0; i <= chunks_amount; ++i) {
            decrypt(data + i * CHUNK_SIZE, key);
        }
    }

    for (int i = 0; i < counter; ++i) {
        printf("%c", data[i]);
    }

    return 0;

}