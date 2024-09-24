#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MSGSIZE 1024
#define FIFOPATH "FIFOpipe"

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
    char msg[MSGSIZE];

    if (mkfifo(FIFOPATH, 0666) < 0) {
        perror_die("ERROR mkfifo");
    }
    
    printf("Enter your message:\n");
    fgets(msg, MSGSIZE, stdin);

    int fd = open(FIFOPATH, O_WRONLY);
    if (fd < 0) {
        if (unlink(FIFOPATH) < 0) {
            perror("ERROR unlink");
        }
        perror_die("ERROR open");
    }

    if (write(fd, (void*)msg, MSGSIZE) < 0) {
        close(fd);
        if (unlink(FIFOPATH) < 0) {
            perror("ERROR unlink");
        }
        perror_die("ERROR write");
    }

    close(fd);
    return EXIT_SUCCESS;
}