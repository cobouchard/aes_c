#include <stdio.h>
#include <stdlib.h>
#include "../include/cypher.h"
#include "../include/multiplication.h"

int main(int argc, char* argv[]){

    struct Word_32 test;
    test.c_words[0]=1;
    test.c_words[1]=4;
    test.c_words[2]=16;
    test.c_words[3]=64;

    print_word32(test);
    rot_word(&test);
    printf("new value \n");
    print_word32(test);
    //
    //left_cyclic_shift(&test);
    //print_word32(test);
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

