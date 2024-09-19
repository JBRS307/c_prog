#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
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

void parse_args(int argc, char** argv, char** filename) {
    if (argc < 2) {
        die("File not provided!\n");
    }
    *(filename) = argv[1];
}

void str_to_upper(char* str) {
    size_t leng = strlen(str);
    for (size_t i = 0; i < leng; i++) {
        str[i] = (char)toupper(str[i]);
    }
}

char* find_comma(char* str) {
    ssize_t leng = strlen(str);
    for (ssize_t i = 0; i < leng; i++) {
        if (str[i] == ',') {
            return &str[i];
        }
    }
    return NULL;
}

int main(int argc, char** argv) {
    char* filename = NULL;
    parse_args(argc, argv, &filename);

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror_die("ERROR fopen");
    }

    bool uppercase = false;
    char buf[BUFSIZ];
    while(!feof(fp)) {
        size_t bytes = fread(buf, sizeof(char), BUFSIZ - 1, fp); // -1 for to make place for \0
        if (ferror(fp)) {
            die("Error reading from file!\n");
        }
        buf[bytes] = '\0';
        if (uppercase) {
            str_to_upper(buf);
        } else {
            char* comma = find_comma(buf);
            if (comma != NULL) {
                uppercase = true;
                str_to_upper(comma);
            }
        }
        printf("%s", buf);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}