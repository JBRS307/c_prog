#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRSIZE 1024

// Returns first character that repeats in the string or NULL terminator
// if no character repeats
char first_repetitive(const char* str) {
    size_t leng = strlen(str);

    char* compar = (char*)malloc(leng + 1);
    compar[0] = '\0';

    for (size_t i = 0; i < leng; i++) {
        if (strchr(compar, (int)str[i]) != NULL) {
            return str[i];
        } else {
            compar[i] = str[i];
            compar[i + 1] = '\0';
        }
    }
    return '\0';
}

int main() {
    char str[STRSIZE];

    printf("Type your string\n");
    scanf("%s", str); // Don't care about buffer overflow

    char c = first_repetitive(str);

    if (c == '\0') {
        printf("No character repeats in string\n");
    } else {
        printf("First character to repeat is %c\n", c);
    }

    return EXIT_SUCCESS;
}