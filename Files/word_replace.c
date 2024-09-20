#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define TEMPNAME "./temp.txt"

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

// Removes all whitespaces on the beginning of the string
char* ltrim(char* str) {
    char* s = str;
    while (isspace(*s)) {
        s++;
    }
    return s;
}

// Cuts first word from the string and trims it
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

typedef enum {
    NONE,
    LEFT,
    RIGHT,
} Direction;

// Replaces all occurences of old_word to new_word in a string str
void replace_word(char* str, const char* old_word, const char* new_word) {
    // At this moment i don't care about overflowing the buffer so if
    // buffer is to slow behavior is undefined

    size_t old_leng = strlen(old_word);
    size_t new_leng = strlen(new_word);

    size_t diff;
    // If new_leng is bigger than old_leng then we shift
    // otherwise we unshift
    Direction direction;
    if (new_leng > old_leng) {
        direction = RIGHT;
        diff = new_leng - old_leng;
    } else if (old_leng > new_leng) {
        direction = LEFT;
        diff = old_leng - new_leng;
    } else {
        direction = NONE;
        diff = 0;
    }

    char* old;
    char* old_end;
    size_t bytes_left;
    while ((old = strstr(str, old_word)) != NULL) {
        if (direction != NONE) {
            old_end = old;
            while (!isspace(*old_end)) {
                old_end++;
            }
            bytes_left = strlen(old_end);
            switch (direction) {
                case RIGHT:
                    memmove((void*)(old_end + diff), (void*)old_end, bytes_left + 1);
                    break;
                case LEFT:
                    memmove((void*)(old_end - diff), (void*)old_end, bytes_left + 1);
                    break;
                case NONE:
                    assert(0 && "Unreachable");
                    break;
            }
        }
        // memcpy instead of strcpy, because I don't want to copy
        // null terminator
        memcpy((void*)old, (void*)new_word, new_leng);
    }
    
}

int main(int argc, char** argv) {
    char* filepath;
    char* old_word;
    char* new_word;

    parse_args(argc, argv, &filepath, &old_word, &new_word);

    FILE* fp_read = fopen(filepath, "r");
    if (fp_read == NULL) {
        perror_die("ERROR fopen");
    }

    FILE* fp_write = fopen(TEMPNAME, "w");
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, fp_read) != NULL) {
        replace_word(buf, old_word, new_word);
        // printf("%s", buf);
        if (fputs(buf, fp_write) == EOF) {
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
    fclose(fp_write);
    fclose(fp_read);

    if (remove(filepath) < 0) {
        perror_die("ERROR remove");
    }
    if (rename(TEMPNAME, filepath) < 0) {
        perror_die("ERROR rename");
    }

    free(old_word);
    free(new_word);
    printf("Success!\n");
    return EXIT_SUCCESS;
}