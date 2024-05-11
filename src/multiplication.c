#include "../include/multiplication.h"

/**
 * multiplies b by {02} in GF(2^8)
 * see NIST doc p9 (4.5)
 * @param b
 */
char x_times(char b){
    return (b>>7) ? (b<<1 ^ 0b00011011) : (b<<1);
}