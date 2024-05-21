#ifndef MAIN_H
#define MAIN_H

struct Params {
    int ecb;
    int gcm;
    char* input_file;
    char* input_key;
    Mode cipher;
};

#endif 