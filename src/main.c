#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cypher.h"
#include "../include/multiplication.h"

void print_key_schedule(struct Key_schedule* key_schedule);

int main(int argc, char* argv[]){

    struct Word_128 block;
    for(int i=0; i!=16; i++){
        block.words[i] = i;
    }

    struct Round_Key key;

    char temp[16] = default_key;

    for(int i=0; i!=4; i++) {
        for(int j=0; j!=4; j++) {
            key.words[i].c_words[j] = temp[i*4+j];
        }
    }


    struct Key_schedule* schedule = (struct Key_schedule*)malloc(sizeof(struct Key_schedule));
    key_expansion(key,schedule);
    print_key_schedule(schedule);

    free(schedule);
}


void print_key_schedule(struct Key_schedule* key_schedule) {
    printf("Key Schedule:\n");
    for (int i = 0; i < 11; ++i) {
        printf("Round %d:\n", i);
        for (int j = 0; j < 4; ++j) {
            printf("    Word %d: ", j);
            for (int k = 0; k < 4; ++k) {
                printf("%02X ", (unsigned char)key_schedule->round_keys[i].words[j].c_words[k]);
            }
            printf("\n");
        }
    }
}