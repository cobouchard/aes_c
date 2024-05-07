#include <stdio.h>
#include "../include/keys.h"


int main(int argc, char* argv[]){
    printf("Hello world!\n");

    union Key_128 mykey;
    for(int i=0; i!=16; i++){
        mykey.words[i]=i;
    }
    //print_key(mykey);

    for(int i =0; i!=256;i++){
        printf("%d\n", sbox[i]);
    }
}

void print_key(union Key_128 key){
    for(int i=0; i!=16; i++){
        printf("%d,",key.words[i]);
    }
    printf("\n");
    for(int i=0; i!=4; i++){
        printf("%d,", key.int_words[i]);
    }
    printf("\n%d", sizeof(union Key_128));
}