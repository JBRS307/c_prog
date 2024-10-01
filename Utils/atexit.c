#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

static volatile bool s_running = false;
void* run_thread() {
    s_running = true;

    unsigned int i = 0;
    while (s_running) {
        printf("%d ", i);
        fflush(stdout);
        usleep(500 * 1000);
        i++;
    }
    return NULL;
}

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

void func_at_exit() {
    printf("Program finished\n");
}

int main() {
    atexit(func_at_exit);

    pthread_t count_thread;
    if ((errno = pthread_create(&count_thread, NULL, run_thread, NULL)) != 0) {
        perror_die("ERROR pthread_create");
    }

    getchar();
    s_running = false;
    if ((errno = pthread_join(count_thread, NULL)) != 0) {
        perror_die("ERROR pthread_join");
    }

    return EXIT_SUCCESS;
}