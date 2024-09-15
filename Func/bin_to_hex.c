#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>

#define STRSIZE 1024
// Subtract to get integer value of number
// represented as char
#define CHARTOINT 48
// Add to integer from range [10, 15] to get its hex symbol
#define INTTOHEX 55

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

// Prints error msg in perror format and
// exits with EXIT_FAILURE code
void perror_die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Checks if string is a valid binary number
bool check_bin(const char* bin, size_t digits) {
    for (size_t i = 0; i < digits; i++) {
        if (bin[i] != '1' && bin[i] != '0') {
            return false;
        }
    }
    return true;
}

// Converts string representation of binary number into decimal integer
int binary_to_decimal(const char* bin, size_t digits) {
    int dec = 0;

    for (ssize_t i = digits - 1; i >= 0; i--) {
        dec += (int)(pow(2.0, (double)(digits - 1 - i)) * (bin[i] - CHARTOINT));
    }

    return dec;
}

// Returns pointer to newly allocated space
// with reverted string. Has to be freed
char* reverse_string(const char* str) {
    ssize_t leng = strlen(str);
    char* res = (char*)malloc(leng + 1);

    for (ssize_t i = leng - 1; i >= 0; i--) {
        res[i] = str[leng - 1 - i];
    }
    res[leng] = '\0';
    return res;
}

// Converts decimal integer into hexadecimal string representation
// returns pointer to dynamically allocated string which has to be freed
char* decimal_to_hex(int dec) {
    if (dec == 0) {
        char* c = (char*)malloc(1);
        *c = '0';
        return c;
    }

    char* buf = (char*)malloc(STRSIZE);
    int i = 0;
    while (dec > 0) {
        int rem = dec % 16;
        char digit;
        if (rem >= 10 && rem <= 15) {
            digit = (char)(rem + INTTOHEX);
        } else {
            digit = (char)(rem + CHARTOINT);
        }

        buf[i] = digit;
        dec /= 16;
        i++;
    }

    buf[i] = '\0';
    
    char* res = reverse_string(buf);
    free(buf);
    return res;

}

int main() {
    char* bin = NULL;
    size_t size = 0;

    printf("Type your binary number: ");

    ssize_t digits = getline(&bin, &size, stdin);
    if (digits < 0) {
        perror_die("ERROR getline");
    }

    if (bin[digits - 1] == '\n') {
        bin[--digits] = '\0';
    }

    if (!check_bin(bin, (size_t)digits)) {
        die("%s is not a valid binary string!\n", bin);
    }

    char* hex = decimal_to_hex(binary_to_decimal(bin, (size_t)digits));
    printf("Hexadecimal form: %s\n", hex);
    free(hex);

    return EXIT_SUCCESS;
}