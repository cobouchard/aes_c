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

    struct Word_128 block;
    for(int i=0; i!=16; i++){
        block.words[i] = i;
    }

    print_word128(block);
    struct State* st = getState(block);

    struct Word_128 block2;
    printf("\n");
    block2 = revert_block(st);
    print_word128(block2);

}

