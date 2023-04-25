#include "../build/codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1024 * 1024 // 1GB

void print_usage(){
    printf("usage: ./Coder key [-e | -d] < input_file\n"
                  "       ./Coder key [-e | -d] < input_file > _output_file\n"
                  "       cat output_file | ./Coder key [-e | -d] > output_file\n");
}

int main(int argc, char *argv[]){
    if (argc != 3){
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

    data[counter] = '\0';
    if (strcmp(argv[2],"-e") == 0){
        /* TODO: Add logic to split every 1024 chars and process with threadpool */
        encrypt(data,key);
    }
    else if (strcmp(argv[2],"-d") == 0){
        /* TODO: Add logic to split every 1024 chars and process with threadpool */
        decrypt(data,key);
    }
    else{
        print_usage();
        return 1;
    }

    printf("%s", data);
    return 0;
}