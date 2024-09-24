#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

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
    char msg[MSGSIZE];

    if (pipe(pipefd) < 0) {
        perror_die("ERROR pipe");
    }
    pid_t child = fork();
    if (child < 0) {
        perror_die("ERROR fork");
    } else if (child == 0) {
        close(pipefd[1]);
        if (read(pipefd[0], (void*)msg, MSGSIZE) < 0) {
            perror_die("ERROR read");
        }
        printf("Message received from pipe:\n%s", msg);
        return EXIT_SUCCESS;
    } else {
        close(pipefd[0]);
        printf("Enter your message:\n");
        fgets(msg, MSGSIZE, stdin);
        if (write(pipefd[1], (void*)msg, MSGSIZE) < 0) {
            kill(child, SIGTERM);
            perror_die("ERROR write");
        }
    }
    int status;
    if (wait(&status) < 0) {
        perror_die("ERROR wait");
    }
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) != EXIT_SUCCESS) {
            exit(EXIT_FAILURE);
        }
    } else if (WIFSIGNALED(status)) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}