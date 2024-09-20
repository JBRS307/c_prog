#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define LETTERS ((int)('z' - 'a' + 1))
#define TEMPNAME "./temp.txt"

typedef enum {
    ENCRYPT,
    DECRYPT,
} Action;

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

    size_t path_leng = strlen(argv[1]);
    *filepath = (char*)malloc(path_leng + 1);
    strcpy(*filepath, argv[1]);
}

int main(int argc, char** argv) {
    Action action;
    int code;
    char* filepath;

    parse_args(argc, argv, &action, &code, &filepath);

    FILE* fp_read = fopen(filepath, "r");
    if (fp_read == NULL) {
        perror_die("ERROR fopen");
    }
    FILE* fp_write = fopen(TEMPNAME, "w");
    if (fp_write == NULL) {
        perror_die("ERROR fopen");
    }
    int c;
    while ((c = fgetc(fp_read)) != EOF) {

    }
    if (ferror(fp_read)) {
        die("Error reading from file!\n");
    }

    return EXIT_SUCCESS;
}