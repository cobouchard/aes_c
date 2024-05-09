#include <stdio.h>
#include <stdlib.h>
#include "../include/cypher.h"

int main(int argc, char* argv[]){
    printf("Hello world!\n");

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

    free(st);
}

