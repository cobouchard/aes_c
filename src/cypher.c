#include "../include/cypher.h"
#include "../include/multiplication.h"
#include <malloc.h>
#include <err.h>
#include <stdlib.h>

const char sbox[] = {0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30, 0x1,0x67,0x2b,0xfe,0xd7,0xab,0x76,
0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
0x4,0xc7,0x23,0xc3,0x18,0x96, 0x5,0x9a, 0x7,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
0x9,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
0x53,0xd1,   0,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9, 0x2,0x7f,0x50,0x3c,0x9f,0xa8,
0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
0xcd, 0xc,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e, 0xb,0xdb,
0xe0,0x32,0x3a, 0xa,0x49, 0x6,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae, 0x8,
0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
0x70,0x3e,0xb5,0x66,0x48, 0x3,0xf6, 0xe,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
0x8c,0xa1,0x89, 0xd,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d, 0xf,0xb0,0x54,0xbb,0x16};

const char inv_sbox[] = {0x52, 0x9,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
                         0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
                         0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95, 0xb,0x42,0xfa,0xc3,0x4e,
                         0x8,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
                         0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
                         0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
                         0x90,0xd8,0xab,   0,0x8c,0xbc,0xd3, 0xa,0xf7,0xe4,0x58, 0x5,0xb8,0xb3,0x45, 0x6,
                         0xd0,0x2c,0x1e,0x8f,0xca,0x3f, 0xf, 0x2,0xc1,0xaf,0xbd, 0x3, 0x1,0x13,0x8a,0x6b,
                         0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
                         0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
                         0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62, 0xe,0xaa,0x18,0xbe,0x1b,
                         0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
                         0x1f,0xdd,0xa8,0x33,0x88, 0x7,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
                         0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a, 0xd,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
                         0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
                         0x17,0x2b, 0x4,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21, 0xc,0x7d};

const struct Word_32 Rcon[] = {
        {{0x01, 0x00, 0x00, 0x00}},
        {{0x02, 0x00, 0x00, 0x00}},
        {{0x04, 0x00, 0x00, 0x00}},
        {{0x08, 0x00, 0x00, 0x00}},
        {{0x10, 0x00, 0x00, 0x00}},
        {{0x20, 0x00, 0x00, 0x00}},
        {{0x40, 0x00, 0x00, 0x00}},
        {{0x80, 0x00, 0x00, 0x00}},
        {{0x1b, 0x00, 0x00, 0x00}},
        {{0x36, 0x00, 0x00, 0x00}}
};

/**
 * this function allocate a new State
 * @param block
 * @return taking a 128 bit block return a state as described in the nist document
 */
struct State* getState(struct Word_128 block){
    struct State* st = (struct State *)malloc(sizeof(struct State));

    for(int i=0; i!=4;i++){
        for(int j=0; j!=4; j++){
            st->matrix[j][i]=block.words[i*4+j];
        }
    }
    return st;
}

struct Word_128 revert_block(struct State* st){
    struct Word_128 block;

    for(int i=0; i!=4;i++){
        for(int j=0; j!=4; j++){
            block.words[i+4*j] = st->matrix[i][j];
        }
    }


    return block;
}

void print_word128(struct Word_128 word){
    for(int i=0; i!=16; i++){
        printf("%d,",word.words[i]);
    }
    printf("\n");
}

void print_word32(struct Word_32 word){
    for(int i=0; i!=4; i++){
        print_char(word.c_words[i]);
        printf("\n");
    }
}

struct Word_32 xor_words32(struct Word_32 w1, struct Word_32 w2){
    struct Word_32 result;
    for(int i=0; i!=4; i++){
        result.c_words[i] = w1.c_words[i] ^ w2.c_words[i];
    }
    return result;
}

/**
 * used in key_expansion() see page 17 equation (5.10)
 * @param word
 */
void rot_word(struct Word_32* word){
    char old = word->c_words[0];
    word->c_words[0] = word->c_words[1];
    word->c_words[1] = word->c_words[2];
    word->c_words[2] = word->c_words[3];
    word->c_words[3] = old;
}

char get_sbox_value(char c){
    short x = first_four_bits(c);
    short y = last_four_bits(c);

    return sbox[x*16+y];
}

char get_inv_sbox_value(char c){
    short x = first_four_bits(c);
    short y = last_four_bits(c);

    return inv_sbox[x*16+y];
}

/**
 * used in key_expansion() see page 17 equation (5.11)
 * @param word
 */
void sub_word(struct Word_32* word){
    for(int i=0; i!=4; i++){
        word->c_words[i] = get_sbox_value(word->c_words[i]);
    }
}

void sub_bytes(struct State* st){
    for(int i=0; i!=4;i++){
        for(int j=0; j!=4; j++){
            st->matrix[i][j] = get_sbox_value(st->matrix[i][j]);
        }
    }
}
void shift_rows(struct State* st){
    //the first line of the state is not changed,
    //each other line are shited in a cycle with an increasing shift

    //line 1
    char old_val = st->matrix[1][0];
    st->matrix[1][0] = st->matrix[1][1];
    st->matrix[1][1] = st->matrix[1][2];
    st->matrix[1][2] = st->matrix[1][3];
    st->matrix[1][3] = old_val;

    //line 2
    old_val = st->matrix[2][1];
    st->matrix[2][0] = st->matrix[2][2];
    st->matrix[2][1] = st->matrix[2][3];
    st->matrix[2][2] = st->matrix[2][0];
    st->matrix[2][3] = old_val;

    //line 3
    old_val = st->matrix[3][2];
    st->matrix[3][0] = st->matrix[3][3];
    st->matrix[3][1] = st->matrix[3][0];
    st->matrix[3][2] = st->matrix[3][1];
    st->matrix[3][3] = old_val;
}

void mix_columns(struct State* st){
    char old_val0;
    char old_val1;
    char old_val2;
    char old_val3;

    for(int column=0; column<4; column++){
        old_val0 = st->matrix[0][column];
        old_val1 = st->matrix[1][column];
        old_val2 = st->matrix[2][column];
        old_val3 = st->matrix[3][column];

        // see page 15 equations (5.8)
        st->matrix[0][column] = (x_times(old_val0)) ^ (multiplication(old_val1,0x03)) ^ old_val2  ^ old_val3;
        st->matrix[1][column] = old_val0 ^ (x_times(old_val1)) ^ (multiplication(old_val2, 0x03)) ^ old_val3;
        st->matrix[2][column] = old_val0 ^ old_val1 ^ (x_times(old_val2)) ^ (multiplication(old_val3, 0x03));
        st->matrix[3][column] = (multiplication(old_val0, 0x03)) ^ old_val1 ^ old_val2 ^ (x_times(old_val3));
    }
}

/**
 * generate 4*(10+1) round keys (words)
 * for aes 128, Nr=10, Nb=Nk=4 (128 bits), a word is a sequence of 4 bytes
 * @param key
 * @param result
 */
void key_expansion(struct Round_Key key, struct Key_schedule* result){
    if(!result){
        errx(EXIT_FAILURE, "result struct to holds round_keys is not allocated\n");
    }

    // the first round key is the key itself
    result->round_keys[0] = key;

    for(int i=4; i<=43; i++){ //4*Nr+3
        //we take the last word
        struct Word_32 temp = result->round_keys[(i-1)/4].words[(i-1)%4];

        if(i%4==0){
            struct Word_32 left_side_xor = temp;
            rot_word(&left_side_xor);
            sub_word(&left_side_xor);
            temp = xor_words32(left_side_xor, Rcon[i/4]);
        }

        result->round_keys[i/4].words[i%4] = xor_words32(result->round_keys[(i-4)/4].words[i%4] , temp);
    }
}

void add_round_key(struct State* st, struct Round_Key key){
    for(int i=0; i!=4; i++){
        struct Word_32 temp = key.words[i];
        for(int j=0; j!=4; j++){
            st->matrix[i][j] = st->matrix[i][j] ^ temp.c_words[j];
        }
    }
}

void inv_shift_rows(struct State* st){
    //this is the inverse function of shift_rows

    //line 2
    char old_value = st->matrix[1][3];
    st->matrix[1][3] = st->matrix[1][2];
    st->matrix[1][2] = st->matrix[1][1];
    st->matrix[1][1] = st->matrix[1][0];
    st->matrix[1][0] = old_value;

    //line 3
    old_value = st->matrix[2][1];
    st->matrix[2][0] = st->matrix[2][2];
    st->matrix[2][1] = st->matrix[2][3];
    st->matrix[2][2] = st->matrix[2][0];
    st->matrix[2][3] = old_value;

    //line 4
    old_value = st->matrix[3][0];
    st->matrix[3][0] = st->matrix[3][1];
    st->matrix[3][1] = st->matrix[3][2];
    st->matrix[3][2] = st->matrix[3][3];
    st->matrix[3][3] = old_value;

}

void inv_sub_bytes(struct State* st){
    for(int i=0; i!=4;i++){
        for(int j=0; j!=4; j++){
            st->matrix[i][j] = get_inv_sbox_value(st->matrix[i][j]);
        }
    }
}

void inv_mix_columns(struct State* st){
    char old_val0;
    char old_val1;
    char old_val2;
    char old_val3;

    for(int column=0; column<4; column++){
        old_val0 = st->matrix[0][column];
        old_val1 = st->matrix[1][column];
        old_val2 = st->matrix[2][column];
        old_val3 = st->matrix[3][column];


        //see page 24 equations (5.15)
        st->matrix[0][column] = multiplication(old_val0, 0x0e) ^
                                multiplication(old_val1, 0x0b) ^
                                multiplication(old_val2, 0x0d) ^
                                multiplication(old_val3, 0x09);

        st->matrix[1][column] = multiplication(old_val0, 0x09) ^
                                multiplication(old_val1, 0x0e) ^
                                multiplication(old_val2, 0x0b) ^
                                multiplication(old_val3, 0x0d);

        st->matrix[2][column] = multiplication(old_val0, 0x0d) ^
                                multiplication(old_val1, 0x09) ^
                                multiplication(old_val2, 0x0e) ^
                                multiplication(old_val3, 0x0b);

        st->matrix[3][column] = multiplication(old_val0, 0x0b) ^
                                multiplication(old_val1, 0x0d) ^
                                multiplication(old_val2, 0x09) ^
                                multiplication(old_val3, 0x0e);
    }
}


void cipher(struct State* st, struct Key_schedule* schedule){
    add_round_key(st, schedule->round_keys[0]);
    for(int round=1; round!=10; round++) { //number of rounds -1
        sub_bytes(st);
        shift_rows(st);
        mix_columns(st);
        add_round_key(st, schedule->round_keys[round]);
    }

    sub_bytes(st);
    shift_rows(st);
    add_round_key(st, schedule->round_keys[10]);
}

void inv_cipher(struct State* st, struct Key_schedule* schedule){
    add_round_key(st, schedule->round_keys[10]);
    for(int round=9; round!=1; round--){
        inv_shift_rows(st);
        inv_sub_bytes(st);
        add_round_key(st,schedule->round_keys[round]);
        inv_mix_columns(st);
    }

    inv_shift_rows(st);
    inv_sub_bytes(st);
    add_round_key(st, schedule->round_keys[0]);
}
