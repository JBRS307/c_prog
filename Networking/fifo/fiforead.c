#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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

    int fd = open(FIFOPATH, O_RDONLY);
    if (fd < 0) {
        perror_die("ERROR open");
    }

    if (read(fd, (void*)msg, MSGSIZE) < 0) {
        perror_die("ERROR read");
    }

    printf("Message read from fifo pipe:\n%s", msg);

    close(fd);
    if (unlink(FIFOPATH) < 0) {
        perror_die("ERROR unlink");
    }
    return EXIT_SUCCESS;
}