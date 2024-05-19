#ifndef AES_C_CYPHER_H
#define AES_C_CYPHER_H

//return the last/first four bits of a given char
#define first_four_bits(c) ((c >>4) & 0x0F)
#define last_four_bits(c) (c & 0x0F)

struct State{
    char matrix[4][4];
};
//For aes-128 the state is a 4*4 matrix with each cell containing a byte, a state contains a whole block

struct Word_128{
    char words[16];
};

struct Word_32{
    char c_words[4];
};

extern const char sbox[];

struct State* getState(struct Word_128* block);
void print_word128(struct Word_128 word);
void print_word32(struct Word_32 word);
void rot_word(struct Word_32* word);
void sub_word(struct Word_32* word);
void sub_bytes(struct State* st);
void shift_rows(struct State* st);
void mix_columns(struct State* st);


#endif //AES_C_CYPHER_H

/**/