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

void cut_word(char* buf, char** left) {
    char* l;
    char* r;

    l = ltrim(buf);
    r = l + 1;
    while (!isspace(*r)) {
        r++;
    }
    *r = '\0';
    *left = l;
}

// Parses arguments
// old_word and new_word are dynamically allocated, must be freed
// after use
void parse_args(int argc, char** argv,
                char** filename, char** old_word, char** new_word) {
    size_t old_leng, new_leng;
    if (argc < 2) {
        die("File not provided!\n");
    } else if (argc < 4) {
        char buf[BUFSIZ];
        printf("Enter word to be replaced: ");
        if (fgets(buf, BUFSIZ, stdin) == NULL) {
            die("Error while reading from stdin!\n");
        }
        char* l;
        cut_word(buf, &l);
        old_leng = strlen(l);
        *old_word = (char*)malloc(old_leng + 1);
        strcpy(*old_word, buf);

        printf("Enter new word: ");
        if (fgets(buf, BUFSIZ, stdin) == NULL) {
            die("Error while reading from stdin!\n");
        }
        cut_word(buf, &l);
        new_leng = strlen(l);
        *new_word = (char*)malloc(new_leng + 1);
        strcpy(*new_word, buf);
    } else {
        old_leng = strlen(argv[2]);
        new_leng = strlen(argv[3]);

        *old_word = (char*)malloc(old_leng + 1);
        *new_word = (char*)malloc(new_leng + 1);
        strcpy(*old_word, argv[2]);
        strcpy(*new_word, argv[3]);
    }
    *filename = argv[1];
}

// Replaces all occurences of old_word to new_word in a string str
void replace_word(char* str, const char* old_word, const char* new_word) {
    // At this moment i don't care about overflowing the buffer
}

int main(int argc, char** argv) {
    char* filename;
    char* old_word;
    char* new_word;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror_die("ERROR fopen");
    }

    char buf[BUFSIZ];
    while(!feof(fp)) {
        if (fgets(buf, BUFSIZ, fp) == NULL) {
            die("Error while reading from file!\n");
        }

        
    }


    free(old_word);
    free(new_word);
    return EXIT_SUCCESS;
}