#ifndef AES_C_CYPHER_H
#define AES_C_CYPHER_H

#define first_four_bits(char) ((char >>4) & 0x0F)
#define last_four_bits(char) (char & 0x0F)

struct State{
    char matrix[4][4];
};
//For aes-128 the state is a 4*4 matrix with each cell containing a byte, a state contains a whole block

union Word_128{
    char words[16];
    int int_words[4];
};

extern const char sbox[];

struct State* getState(union Word_128* block);
void print_word128(union Word_128 word);
void sub_bytes(struct State* st);
void shift_rows(struct State* st);


#endif //AES_C_CYPHER_H

/**/