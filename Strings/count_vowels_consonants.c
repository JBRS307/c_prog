#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 1024

// Counts vowels and consonants int string, saves results in v_count and c_count
// String str MUST end with NULL terminator, otherwise behaviour of the function is undefined
void count_vc(const char* str, unsigned int* v_count, unsigned int* c_count) {
    char vowels[] = "aeiouAEIOU";

    *v_count = *c_count = 0;

    while (*str != '\0') {
        if ((*str >= 'a' && *str <= 'z') ||
             (*str >= 'A' && *str <= 'Z')) {
            
            if (strchr(vowels, (int)*str) != NULL) {
                (*v_count)++;
            } else {
                (*c_count)++;
            }
        }
        str++;
    }
}

int main() {
    char str[STRSIZE];

    printf("Type your sentence: ");
    if (fgets(str, STRSIZE, stdin) == NULL) {
        fprintf(stderr, "ERROR fgets\n");
        exit(EXIT_FAILURE);
    }

    unsigned int v_count, c_count;

    count_vc(str, &v_count, &c_count);

    printf("Vowels: %d\n"
           "Consonants: %d\n",
           v_count, c_count);

    return EXIT_SUCCESS;
}