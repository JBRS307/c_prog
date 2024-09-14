#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Checks if string is a valid binary number
bool check_bin(const char* bin) {
    size_t leng = strlen(bin);

    for (size_t i = 0; i < leng; i++) {
        if (bin[i] != '1' && bin[i] != '0') {
            return false;
        }
    }
    return true;
}

// Converts string representation of binary number into decimal
int binary_to_decimal(const char* bin) {
    int dec = 0;
    size_t digits = strlen(bin);

    for (size_t i = digits - 1, j = 0; i >= 0; i--, j++) {
        // TODO
    }
}

int main() {


    return EXIT_SUCCESS;
}