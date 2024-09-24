#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#define MSGSIZE 1024

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

int main() {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror_die("ERROR pipe");
    }

    char msg[MSGSIZE];

    int n;
    printf("Enter number of messages: ");
    if (scanf("%d%*c", &n) != 1) {
        die("Invalid number of messages!\n");
    }
    

    for (int i = 0; i < n; i++) {
        printf("Enter your message:\n");
        fgets(msg, MSGSIZE, stdin);
        if (write(pipefd[1], (void*)msg, MSGSIZE) < 0) {
            perror_die("ERROR write");
        }
    }
    close(pipefd[1]);

    printf("Reading messages from pipe:\n");
    for (int i = 0; i < n; i++) {
        if (read(pipefd[0], (void*)msg, MSGSIZE) < 0) {
            perror_die("ERROR read");
        }
        printf("%s", msg);
    }
    close(pipefd[0]);

    return EXIT_SUCCESS;
}