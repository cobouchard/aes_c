#include <stdlib.h>
#include <string.h>
#include "../include/cypher.h"
#include "../include/modes.h"
#include "../include/main.h"
#include <getopt.h>
#include <err.h>

struct Params parameters = {
        .ecb = 1,
        .gcm = 0,
        .input_file = "alice.txt",
        .cipher = CIPHER,
        .input_key = NULL
};

int main(int argc, char* argv[]){

    struct Round_Key key;

    static struct option long_options[]= {
            {"gcm", no_argument, 0, 'g'},
            {"help", no_argument, 0, 'h'},
            {"decipher", no_argument, 0, 'd'},
            {"test", no_argument, 0, 't'},
            {"key", required_argument,0, 'k'}
    };

    int c;
    int option_index=0;
    do{
        c= getopt_long(argc, argv, "hgdtk:", long_options, &option_index);
        switch (c) {
            case 'h':
                printf("-k {key-path} \t to cipher the content of the file\n");
                printf("-d \t to decipher instead of ciphering\n");
                printf("-h \t to print this help\n");
                exit(EXIT_SUCCESS);

            case 't':
                char temp[16] = default_key;
                for(int i=0; i!=4; i++) {
                    for(int j=0; j!=4; j++) {
                        key.words[i].c_words[j] = temp[i*4+j];
                    }
                }
                mode_ecb(parameters.input_file, "output.txt", key, parameters.cipher);
                exit(EXIT_SUCCESS);

            case 'g':
                printf("Cipher using GCM mode and AES-128, \"alice.sage\" by default, output will be written in output.txt\n");
                parameters.gcm=1;
                break;
            case 'd':
                printf("Deciphering\n");
                parameters.cipher=DECIPHER;
                break;

            case 'k':
                parameters.input_key = optarg;
                printf("Using %s as key\n", parameters.input_key);
        }

    }while(c != -1);

    //reading key as first input
    parameters.input_file = argv[optind];
    optind++;
    if(parameters.input_key==NULL){
        printf("No key given, default key will be used\n");
        char temp[16] = default_key;
        for(int i=0; i!=4; i++) {
            for(int j=0; j!=4; j++) {
                key.words[i].c_words[j] = temp[i*4+j];
            }
        }
    }

    else{
        FILE* input_file;
        input_file = fopen(parameters.input_key, "rb");

        if(input_file==NULL)
            errx(EXIT_FAILURE, "Couldn't open %s to read input key\n", parameters.input_key);


        read_key(input_file, &key);

        //checking second input for document to cipher/decipher, if none using alice.sage
        if(parameters.input_file==NULL)
            printf("No document given to cipher, ciphering \"alice.sage\" \n");

        else{
            input_file = fopen(parameters.input_file, "rb");
            if(input_file==NULL)
                errx(EXIT_FAILURE, "Couldn't open %s to read input document\n", parameters.input_file);

            printf("Ciphering %s \n", parameters.input_file);
            fclose(input_file);
        }
    }

    char* output_file="cipher.txt";
    if(parameters.cipher==DECIPHER)
        output_file="decipher.txt";
    if(parameters.gcm){
        mode_gcm(parameters.input_file, output_file, key, parameters.cipher);
    }
    else if(parameters.ecb){
        mode_ecb(parameters.input_file, output_file, key, parameters.cipher);
    }

    printf("Output written in \"%s\"\n", output_file);
}

/**
 * reading a file to import a key to cipher
 * @param filename path to file
 * @param key result will be written here
 */
void read_key(FILE* file, struct Round_Key *key) {
    for (int i = 0; i < 4; ++i) {
        size_t read_count = fread(key->words[i].c_words, sizeof(char), 4, file);
        if (read_count != 4) {
            if (feof(file)) {
                fprintf(stderr, "Unexpected end of file.\n");
            } else {
                perror("Failed to read data");
            }
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

