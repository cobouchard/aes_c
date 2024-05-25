#include "../include/multiplication.h"
#include <stdio.h>

/**
 * multiplies b by {02} in GF(2^8)
 * see NIST documentation, page 9 equation (4.5)
 * @param b
 */
char x_times(char b){
    return (b>>7) ? (b<<1 ^ XTIMES_XOR_VALUE) : (b<<1);
}

/**
 * multiplying by {02} in GF(2^8) (n_applications) times
 * @param b 
 * @param n_applications
 * @return
 */
char apply_x_times(char b, int n_applications){
    if(n_applications==0)
        return b;

    return apply_x_times(x_times(b),--n_applications);
}

/**
 * for optimisation purposes, enter b<a
 * @param a
 * @param b
 * @return a * b in GF(2^8)
 */
char multiplication(char a, char b){
    char product = 0;
    int n = 0; //number of times we apply x_times

    while(b!=0){
        if(first_bit(b)){
            product ^= apply_x_times(a,n);
        }
        b=b>>1;
        n+=1;
    }

    return product;
}

void print_char(char c){
    for(int i=0; i<8; i++)
        printf("%d", !!((c << i) & 0x80));
}