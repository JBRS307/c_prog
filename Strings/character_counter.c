#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 1024

// Saves characters of string str into chr array, saves count
// of each character in respective indexes of count array
// chr and count must be at least length of str
void count_chars(const char* str, char* chr, int* count) {
    size_t n = strlen(str);
    chr[0] = '\0';

    int chr_index = 0;
    for (size_t i = 0; i < n; i++) {
        char* c = strchr(chr, (int)str[i]);
        if (c == NULL) {
            chr[chr_index] = str[i];
            count[chr_index] = 1;
            chr[++chr_index] = '\0';
        } else {
            int ind = (int)(c - chr);
            count[ind]++;
        }
    }
}

int main() {
    char str[STRSIZE];

    printf("Enter your string\n");
    scanf("%s", str); // Don't care about buffer overflow

    char chr[STRSIZE];
    int count[STRSIZE];

    count_chars(str, chr, count);

    size_t chars_leng = strlen(chr);
    for (size_t i = 0; i < chars_leng; i++) {
        printf("%c: %d\n", chr[i], count[i]);
    }

    return EXIT_SUCCESS;
}