#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
    int32_t a, b, res;

    printf("Enter 2 numbers to multiply: ");
    if (scanf("%d%d", &a, &b) != 2) {
        die("Invalid input!\n");
    }

    asm volatile (
        "imull %%ebx, %%eax;"
        : "=a" (res)
        : "a" (a), "b" (b)
    );

    printf("Result: %d\n", res);

    return EXIT_SUCCESS;
}