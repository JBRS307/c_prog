#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define ASCIICONV 48
#define BINBLOCK 64

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void perror_die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void reverse_str(char* str) {
    size_t leng = strlen(str);
    char* l = str;
    char* r = str + leng - 1;
    while (l < r) {
        char temp = *l;
        *l = *r;
        *r = temp;
        l++;
        r--;
    }
}

// Converts decimal number to binary and stores result in a string,
// returns pointer to that string
// String is dynamically allocated, must be freed
char* dec_to_bin(unsigned int dec) {
    if (dec == 0) {
        char* c = (char*)malloc(2);
        *c = '0';
        *(c + 1) = '\0';
        return c;
    }

    size_t blocks = 1, idx = 0;
    char* bin = (char*)malloc(BINBLOCK);
    // when we run out of memory we use realloc to double size of bin

    unsigned int digit;
    while (dec > 0) {
        digit = dec & 1;
        bin[idx++] = digit + ASCIICONV;
        dec >>= 1;
        if (idx == blocks * BINBLOCK) {
            bin = (char*)realloc(bin, ++blocks * BINBLOCK);
        }
    }
    bin[idx] = 0; 
    reverse_str(bin);
    return bin;    
}

int main() {
    unsigned int dec;
    printf("Enter positive decimal number: ");
    if (scanf("%u", &dec) != 1) {
        die("Invalid input!\n");
    }

    char* bin = dec_to_bin(dec);

    printf("Binary form of %u is %s\n", dec, bin);

    free(bin);
    return EXIT_SUCCESS;
}