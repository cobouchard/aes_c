#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "../include/modes.h"

/**
 *
 * @param input_file file to be encrypted, default alice.sage
 * @param output_file file where the output will be written, pass 0 as a parameter if you don't want any save (for testing speed)
 * @param key
 */
void mode_ecb(char* input_path, char* output_path, struct Round_Key key, Mode mode){
    if(output_path==0)
        output_path = "output.txt";

    if(input_path==0)
        input_path = "alice.sage";

    FILE *inputFile, *outputFile;
    inputFile = fopen(input_path, "r");
    if(inputFile == NULL){
        errx(EXIT_FAILURE,"Cannot open %s input file\n", input_path);
    }
    outputFile = fopen(output_path, "w");
    if(outputFile == NULL){
        fclose(inputFile);
        errx(EXIT_FAILURE, "Cannot open file for writing result\n");
    }

    struct Key_schedule* schedule = (struct Key_schedule*)malloc(sizeof(struct Key_schedule));
    if(schedule==NULL){
        errx(EXIT_FAILURE, "Failed allocation of schedule in mode_ecb()\n");
    }
    key_expansion(key,schedule);

    struct State* st;
    struct Word_128 block;
    char c;
    int current_index=0;

    while ((c = fgetc(inputFile)) != EOF) {
        block.words[current_index] = c;
        current_index = (current_index+1)%16;
        if(current_index==0){
            //we have a complete block, we can cipher it
            write_block(st, block, schedule, outputFile, mode);
        }
    }
    //if the last block was not full, we add 0 to cipher the last block
    if(current_index!=0){
        for(;current_index!=16;current_index++){
            block.words[current_index]=0;
        }
        write_block(st, block, schedule, outputFile, mode);
    }



    fclose(inputFile);
    fclose(outputFile);
    free(schedule);
}

void mode_gcm(char* input_file, char* output_file, struct Round_Key key, Mode mode){
    printf("Unimplemented\n");
}

void write_block(struct State* st, struct Word_128 block, struct Key_schedule* schedule, FILE* outputFile, Mode mode){
    struct Word_128 output_block;

    st=getState(block);
    if(st==NULL){
        errx(EXIT_FAILURE, "Failed allocation of state st in write_block()");
    }

    if(mode==CIPHER){
        cipher(st,schedule);
    }
    else{
        inv_cipher(st,schedule);
    }

    output_block = revert_block(st);
    for(int i=0; i!=16; i++){
        fputc(output_block.words[i],outputFile);
    }
    free(st);
}