#include <stdio.h>
#include <stdlib.h>
#include "../include/cypher.h"
#include "../include/multiplication.h"

int main(int argc, char* argv[]){
    char a = 0x57;
    char b = 0x03;

    char c = multiplication(a,b);
    printf("final result \n");
    print_char(x_times(0x57));
    /*printf("Hello world!\n");

    union Word_128 mykey;
    for(int i=0; i!=16; i++){
        mykey.words[i]=i;
    }
    printf("%d",sizeof(&sbox));
    struct State* st = getState(&mykey);

    for(int i=0; i!=4;i++) {
        for (int j = 0; j != 4; j++){
            printf("%d\n", st->matrix[i][j]);
        }
    }

    free(st);*/
}

