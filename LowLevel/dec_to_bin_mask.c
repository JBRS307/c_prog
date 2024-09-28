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

// Converts decimal number to binary
// Returns pointer to string containing binary number
// Memory is dynamically allocated
char* dec_to_bin(unsigned int dec) {
    if (dec == 0) {
        char* c = (char*)malloc(2);
        *c = '0';
        *(c + 1) = '\0';
    }

    // TODO
}

int main() {
    unsigned int dec;
    printf("Enter positive decimal number: ");
    if (scanf("%u", &dec) != 1) {
        die("Invalid input!\n");
    } 



    return EXIT_SUCCESS;
}