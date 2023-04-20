#include "../build/codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_usage()
{
    printf("usage: ./Coder key [-e | -d] < input_file\n"
                  "       ./Coder key [-e | -d] < input_file > _output_file\n"
                  "       cat output_file | ./Coder key [-e | -d] > output_file\n");
    printf("!! data more than 1024 char will be ignored !!\n");
}

int main(int argc, char *argv[]){
    if (argc != 3){
        print_usage();
        return 0;
    }

    int key = atoi(argv[1]);
    printf("key is %i \n",key);

    char c;
    int counter = 0;
    int dest_size = 1024;
    char data[dest_size];
    bzero(data, dest_size);

    while ((c = getchar()) != EOF){
      data[counter] = c;
      counter++;

      if (counter == dest_size - 1){
          print_usage();
          return 1;
      }
    }

    printf("%d", counter);

    data[counter] = '\0';
    if (strcmp(argv[2],"-e") == 0){
        encrypt(data,key);
    }
    else if (strcmp(argv[2],"-d") == 0){
        decrypt(data,key);
    }
    else{
        print_usage();
        return 1;
    }

    printf("%s", data);
    return 0;
}