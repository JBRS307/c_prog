#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void perror_die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Reverses string of length n in place
void reverse_string_in_place(char* const str, size_t n) {
    char* left = str;
    char* right = str + (n - 1);

    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;

        right--;
        left++;
    }
}

int main() {
    char* str = NULL;
    printf("Type string to reverse\n");
    
    size_t bytes = 0;
    if (getline(&str, &bytes, stdin) < 0) {
        perror_die("ERROR getline");
    }
    size_t leng = strlen(str);
    if (str[leng - 1] == '\n') {
        str[--leng] = '\0';
    }

    printf("String to reverse\n%s\n", str);
    reverse_string_in_place(str, leng);
    printf("Reversed string\n%s\n", str);

    free(str);

    return EXIT_SUCCESS;
}