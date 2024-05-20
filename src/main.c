#include <stdlib.h>
#include <string.h>
#include "../include/cypher.h"
#include "../include/modes.h"

int main(int argc, char* argv[]){
    //defining the key
    struct Round_Key key;
    char temp[16] = default_key;
    for(int i=0; i!=4; i++) {
        for(int j=0; j!=4; j++) {
            key.words[i].c_words[j] = temp[i*4+j];
        }
    }

    mode_ecb("alice.sage", 0, key, CIPHER);

    //defining the input and state
//    struct State* st;
//    struct Word_128 block;
//    char temp2[16] = default_input;
//    memcpy(block.words, temp2, sizeof(temp2));
//    st=getState(block);
//
//
//
//    //calculating round keys
//    struct Key_schedule* schedule = (struct Key_schedule*)malloc(sizeof(struct Key_schedule));
//    key_expansion(key,schedule);
//    //print_key_schedule(schedule);
//
//    //cipher the block and revert to word
//    cipher(st,schedule);
//    inv_cipher(st,schedule);
//
//    block = revert_block(st);
//
//    //print the result
//    print_word128_hexa(block);
//
//    free(st);
//    free(schedule);
}

