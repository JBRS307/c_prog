#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 1024

int main() {
    char str[STRSIZE];

    if (fgets(str, STRSIZE, stdin) == NULL) {
        fprintf(stderr, "ERROR fgets\n");
        exit(EXIT_FAILURE);
    }

    // TODO vowels and consonants counter

    return EXIT_SUCCESS;
}