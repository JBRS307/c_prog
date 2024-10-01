#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define ASCIICONV 48
#define BINBLOCK (32+1)

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

// Converts decimal number to binary
// Returns pointer to string containing binary number
// Memory is dynamically allocated
char* dec_to_bin(unsigned int dec) {
    if (dec == 0) {
        char* c = (char*)malloc(2);
        *c = '0';
        *(c + 1) = '\0';
        return c;
    }

    unsigned int mask = 1 << 31;

    char* bin = (char*)malloc(BINBLOCK);
    *bin = 0;
    char* curr_bin_digit = bin;

    while (mask != 0) {
        if (dec & mask) {
            *curr_bin_digit = '1';
        } else {
            *curr_bin_digit = '0';
        }
        curr_bin_digit++;
        mask >>= 1;
    }
    *curr_bin_digit = 0;

    curr_bin_digit = bin;
    while (*curr_bin_digit == '0') {
        curr_bin_digit++;
    }

    char* res = (char*)malloc(BINBLOCK);
    *res = 0;
    strcpy(res, curr_bin_digit);

    free(bin);
    return res;
}

int main() {
    unsigned int dec;
    printf("Enter positive decimal number: ");
    if (scanf("%u", &dec) != 1) {
        die("Invalid input!\n");
    } 

    char* bin = dec_to_bin(dec);

    printf("Binary form of %d is %s\n", dec, bin);

    free(bin);
    return EXIT_SUCCESS;
}