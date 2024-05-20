#ifndef MODES_H
#define MODES_H

#include "cypher.h"
#include <stdio.h>

typedef enum {
    CIPHER,
    DECIPHER
} Mode;

void mode_ecb(char* input_file, char* output_file, struct Round_Key key, Mode mode);

void write_block(struct State* st, struct Word_128 block, struct Key_schedule* schedule, FILE* outputFile, Mode mode);

#endif