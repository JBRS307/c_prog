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
        die("File not provided!\n");
    }

    *filename = argv[1];
}

// Returns pointer to new reversed string
// Dynamically allocated, must be freed after use
char* reverse_str(const char* str) {
    size_t leng = strlen(str);
    char* rev = (char*)malloc(leng + 1);

    for (size_t i = 0, j = leng - 1; i < leng; i++, j--) {
        rev[i] = str[j];
    }
    rev[leng] = '\0';
    return rev;
}

int main(int argc, char** argv) {
    char* filename = NULL;
    parse_args(argc, argv, &filename);

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror_die("ERROR fopen");
    }

    char buf[BUFSIZ];
    char* reversed = NULL;
    long pos;
    size_t bytes;
    long i = 1;
    if (fseek(fp, 0L, SEEK_END) < 0) {
        perror_die("ERROR fseek");
    }
    while ((pos = ftell(fp)) >= (BUFSIZ - 2)) {
        if (fseek(fp, -(BUFSIZ - 1), SEEK_CUR) < 0) {
            perror_die("ERROR fseek");
        }
        bytes = fread(buf, 1, BUFSIZ - 1, fp);
        if (ferror(fp)) {
            die("Error while reading from file!\n");
        }
        buf[bytes] = '\0';

        reversed = reverse_str(buf);
        printf("%s", reversed);
        free(reversed);
        if (fseek(fp, -(BUFSIZ - 1), SEEK_CUR) < 0) {
            perror_die("ERROR fseek");
        }
        i++;
    }
    if (pos < 0) {
        perror_die("ERROR ftell");
    }
    if (fseek(fp, 0L, SEEK_SET) < 0) {
        perror_die("ERROR fseek");
    }

    bytes = fread(buf, 1, pos + 1, fp);
    if (ferror(fp)) {
        die("Error while reading from file!\n");
    }
    buf[bytes] = '\0';
    reversed = reverse_str(buf);
    printf("%s", reversed);
    free(reversed);

    fclose(fp);
    return EXIT_SUCCESS;
}