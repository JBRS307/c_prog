#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define STRSIZE 1024

// Add value to change uppercase letter into lowercase
// Subtract to do the opposite
#define CONVERSION_CONST 32

// Prints message to stderr and exits with EXIT_FAILURE code
void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

// Converts all vowels in str to uppercase
// String str MUST end with NULL terinator
void vowels_to_uppercase(char* str) {
    const char vowels[] = "aeiou";

    while (*str != '\0') {
        if (strchr(vowels, (int)*str) != NULL) {
            *str -= CONVERSION_CONST;
        }
        str++;
    }
}

int main() {
    char str[STRSIZE];

    printf("Type your sentence: ");
    if (fgets(str, STRSIZE, stdin) == NULL) {
        die("ERROR fgets\n");
    }

    vowels_to_uppercase(str);

    printf("Transformed sentence:\n");
    printf("%s\n", str);

    return EXIT_SUCCESS;
}