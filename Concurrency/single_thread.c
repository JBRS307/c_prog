#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void perror_die(const char* fmt) {
    perror(fmt);
    exit(EXIT_FAILURE);
}

void* run_thread() {
    printf("Runnig thread %lu\n", pthread_self());
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    putchar('\n');
    return NULL;
}

int main() {
    pthread_t tid;
    if (pthread_create(&tid, NULL, run_thread, NULL) != 0) {
        die("An error occured while creating new thread!\n");
    }
    printf("Waiting for thread %lu to finish\n", tid);
    if (pthread_join(tid, NULL) != 0) {
        die("An error occured while joining the thread %lu!\n", tid);
    }
    printf("Thread %lu finished\n", tid);

    return EXIT_SUCCESS;
}