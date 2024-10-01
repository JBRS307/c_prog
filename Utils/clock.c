#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

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

void measured_func() {
    for (int i = 1; i <= 10000; i++) {
        printf("%d", i);
    }
}

int main() {
    #ifdef __BENCHMARK__
        clock_t start, end;
        double ms;
        start = clock();
        measured_func();
        end = clock();
        if (start < 0 || end < 0) {
            fprintf(stderr, "CPU time used is not available!. Measurement aborted!\n");
        } else {
            ms = 1000 * (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nTime consumed: %lfms\n", ms);
        }
    #else
        measured_func();
    #endif

    return EXIT_SUCCESS;
}