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
    int32_t a, b, quot, rem;
    printf("Enter 2 numbers to divide: ");
    if (scanf("%d%d", &a, &b) != 2) {
        die("Invalid input!\n");
    }
    if (b == 0) {
        die("Divisor cannot be 0!\n");
    }

    asm volatile (
        "divl %%ebx;"
        "movl %%edx, %0"
        : "=b" (rem), "=r" (quot)
        : "a" (a), "b" (b), "d" (0)
    );

    printf(
        "Quotient: %d\n"
        "Remainder: %d\n",
        quot, rem
    );

    return EXIT_SUCCESS;
}