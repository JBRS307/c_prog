#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

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

char* ltrim(char* str) {
    char* s = str;
    while (isspace(*s)) {
        s++;
    }
    return s;
}

void parse_args(int argc, char** argv,
                char** filename, char** old_word, char** new_word) {
    if (argc < 2) {
        die("File not provided!\n");
    } else if (argc < 4) {
        char buf[BUFSIZ];
        printf("Enter word to be replaced: ");
        if (fgets(buf, BUFSIZ, stdin) == NULL) {
            die("Error while reading from stdin!\n");
        }
        char* l = ltrim(buf);
        char* r = l + 1;
        while (!isspace(*r)) {
            r++;
        }
        *r = '\0';
        size_t old_leng = strlen(l);
        *old_word = (char*)malloc(old_leng + 1);
        strcpy(*old_word, l);
    }
}

int main(int argc, char** argv) {
    char* filename;
    char* old_word;
    char* new_word;

    return EXIT_SUCCESS;
}