#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include <errno.h>

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

void* run_thread1() {
    printf("Runnning thread %lu\n", pthread_self());
    for (int i = 1; i <= 5; i++) {
        printf("%d\n", i);
    }
    return NULL;
}

void* run_thread2() {
    printf("Runnning thread %lu\n", pthread_self());
    for (int i = 11; i <= 15; i++) {
        printf("%d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    if ((errno = pthread_create(&tid1, NULL, run_thread1, NULL)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_create(&tid2, NULL, run_thread2, NULL)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_join(tid1, NULL)) != 0) {
        perror_die("ERROR pthread_join");
    }
    if ((errno = pthread_join(tid2, NULL)) != 0) {
        perror_die("ERROR pthread_join");
    }
    printf("All threads finished!\n");


    return EXIT_SUCCESS;
}