#ifndef AES_C_CYPHER_H
#define AES_C_CYPHER_H

//return the last/first four bits of a given char
#define first_four_bits(c) ((c >>4) & 0x0F)
#define last_four_bits(c) (c & 0x0F)

//#define default_key {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}
#define default_key {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c}


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

struct Round_Key{
    struct Word_32 words[4];
};

struct Key_schedule{
    struct Round_Key round_keys[11]; //10 rounds in aes-128, 11 applications of add_round_key
};

extern const char sbox[];
extern const char inv_sbox[];
extern const struct Word_32 Rcon[];

struct State* getState(struct Word_128 block);
struct Word_128 revert_block(struct State* st);
void print_word128(struct Word_128 word);
void print_word32(struct Word_32 word);
void print_word32_hexa(struct Word_32 word);
struct Word_32 xor_words32(struct Word_32 w1, struct Word_32 w2);
void rot_word(struct Word_32* word);
void sub_word(struct Word_32* word);
char get_sbox_value(char c);
char get_inv_sbox_value(char c);
void sub_bytes(struct State* st);
void shift_rows(struct State* st);
void mix_columns(struct State* st);
void key_expansion(struct Round_Key key, struct Key_schedule* result);
void add_round_key(struct State* st, struct Round_Key key);
void inv_shift_rows(struct State* st);
void inv_sub_bytes(struct State* st);
void inv_mix_columns(struct State* st);
void cipher(struct State* st, struct Key_schedule* schedule);
void inv_cipher(struct State* st, struct Key_schedule* schedule);

#endif //AES_C_CYPHER_H

/**/