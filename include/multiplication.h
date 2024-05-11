#ifndef AES_C_MULTIPLICATION_H
#define AES_C_MULTIPLICATION_H

#define XTIMES_XOR_VALUE 0b00011011
#define first_bit(b) (b & 1)

char x_times(char b);
char apply_x_times(char b, int n_applications);
char multiplication(char a, char b);
void print_char(char c);

#endif //AES_C_MULTIPLICATION_H