#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define BINLENGTH 1024
#define ASCIICONV 48

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

bool is_valid_bin(const char* bin) {
    while (*bin != 0) {
        if (*bin != '1' && *bin != '0') {
            return false;
        }
        bin++;
    }
    return true;
}

unsigned int bin_to_decimal(const char* bin) {
    size_t bin_length = strlen(bin);
    const char* r = bin + bin_length - 1;

    unsigned int res = 0, power = 0;
    unsigned int digit;
    while (r >= bin) {
        digit = *r - ASCIICONV;
        res += digit << power;
        power++;
        r--;
    }
    return res;
}

int main() {
    char bin[BINLENGTH];
    printf("Enter positive binary number: ");
    fgets(bin, BINLENGTH, stdin);
    if (ferror(stdin)) {
        die("Error reading from stdin!\n");
    }
    size_t bin_length = strlen(bin);
    if (bin[bin_length - 1] == '\n') {
        bin[--bin_length] = 0;
    }

    if (!is_valid_bin(bin)) {
        die("Number is not a positive binary number!\n");
    }

    printf("Decimal form of binary number %s is %u\n", bin, bin_to_decimal(bin));

    return EXIT_SUCCESS;
}