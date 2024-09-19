#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

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

void parse_args(int argc, char** argv, char** filename) {
    if (argc < 2) {
        die("Filename not provided!\n");
    }

    *filename = argv[1];
}

// Counts vowels in a string
int count_vowels(const char* str) {
    char vowels[] = "aeiouAEIOU";

    size_t leng = strlen(str);

    int counter = 0;
    for (size_t i = 0; i < leng; i++) {
        if (strchr(vowels, str[i]) != NULL) {
            counter++;
        }
    }
    return counter;
}

int main(int argc, char** argv) {
    char* filename = NULL;
    parse_args(argc, argv, &filename);

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror_die("ERROR fopen");
    }

    long vowels = 0;
    char buf[BUFSIZ];
    while (!feof(fp)) {
        size_t bytes = fread(buf, 1, BUFSIZ - 1, fp);
        if (ferror(fp)) {
            die("Error while reading from file!\n");
        }
        buf[bytes] = '\0';

        vowels += count_vowels(buf);
    }
    printf("Vowels in file: %ld\n", vowels);
    
    fclose(fp);
    return EXIT_SUCCESS;
}