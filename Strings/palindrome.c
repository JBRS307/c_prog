#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 1024

// Reverses string, saves result in rev
// Situation when string is longer than rev buffer is undefined
void reverse_string(const char* str, char* rev) {
    size_t leng = strlen(str);
    for (size_t i = 0, j = leng - 1; i < leng; i++, j--) {
        rev[i] = str[j];
    }
    rev[leng] = '\0';
}

int main() {
    char str[STRSIZE];
    char rev[STRSIZE];

    printf("Type your string\n");
    scanf("%s", str);
    // At this moment possible buffer overflow is not something I care about

    reverse_string(str, rev);
    if (strcmp(str, rev) == 0) {
        printf("String is palindrome!\n");
    } else {
        printf("String is NOT palindrome!\n");
    }

    return EXIT_SUCCESS;
}