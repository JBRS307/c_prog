#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define LETTERS ((int)('z' - 'a' + 1))
#define TEMPNAME "./temp.txt"

typedef enum {
    ENCRYPT,
    DECRYPT,
} Action;
// Technically decryption mode can be used for encryption and viceversa
// The person just should remember which one they used

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

void parse_args(int argc, char** argv,
                Action* action, int* code, char** filepath) {
    switch (argc) {
        case 0:
        case 1:
            die("File not provided!\n");
            break;
        case 2:
            printf("Enter code: ");
            if (scanf("%d", code) != 1) {
                die("Invalid input!\n");
            }
            *action = ENCRYPT;
            break;
        case 3:
            *action = ENCRYPT;
            *code = atoi(argv[2]) % LETTERS;
            break;
        default:
            short num_action = (short)atoi(argv[3]);
            if (num_action != 1 && num_action != 0) {
                die("Incorrect action!\n");
            }
            *action = (Action)num_action;
            *code = atoi(argv[2]) % LETTERS;
            break;
    }

    *filepath = argv[1];
}

// Moves alphabetic character by code
int transpone(int c, int code) {
    int c_new;
    if (islower(c)) {
        c_new = c + code;
        if (c_new > 'z') {
            c_new = ('a' - 1) + (c_new - 'z');
        } else if (c_new < 'a') {
            c_new = ('z' + 1) - ('a' - c_new);
        }
    } else if (isupper(c)) {
        c_new = c + code;
        if (c_new > 'Z') {
            c_new = ('A' - 1) + (c_new - 'Z');
        } else if (c_new < 'A') {
            c_new = ('Z' + 1) - ('A' - c_new);
        }
    } else {
        c_new = c;
    }
    return c_new;
}

int main(int argc, char** argv) {
    Action action;
    int code;
    char* filepath;

    parse_args(argc, argv, &action, &code, &filepath);

    if (action == DECRYPT) {
        code *= -1;
    }

    FILE* fp_read = fopen(filepath, "r");
    if (fp_read == NULL) {
        perror_die("ERROR fopen");
    }
    FILE* fp_write = fopen(TEMPNAME, "w");
    if (fp_write == NULL) {
        fclose(fp_read);
        perror_die("ERROR fopen");
    }
    int c;
    while ((c = fgetc(fp_read)) != EOF) {
        int c_new = transpone(c, code);
        if (fputc(c_new, fp_write) == EOF) {
            fclose(fp_read);
            fclose(fp_write);
            if (remove(TEMPNAME) < 0) {
                perror("ERROR remove");
            }
            die("Error while writing to file!\n");
        }
    }
    if (ferror(fp_read)) {
        fclose(fp_read);
        fclose(fp_write);
        if (remove(TEMPNAME) < 0) {
            perror("ERROR remove");
        }
        die("Error while reading from file!\n");
    }

    fclose(fp_read);
    fclose(fp_write);

    if (remove(filepath) < 0) {
        perror_die("ERROR remove");
    }

    if (rename(TEMPNAME, filepath) < 0) {
        perror_die("ERROR rename");
    }

    printf("Success!\n");
    return EXIT_SUCCESS;
}