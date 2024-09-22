#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

pthread_t tid1, tid2;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int common = 0; // Should be 2 after both threads are run

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

void* run_thread() {
    pthread_mutex_lock(&lock);
    pthread_t id = pthread_self();

    if (pthread_equal(id, tid1)) {
        printf("First thread is running!\n");
    } else {
        printf("Second thread is running!\n");
    }
    sleep(3);
    common++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    if ((errno = pthread_create(&tid1, NULL, run_thread, NULL)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_create(&tid2, NULL, run_thread, NULL)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_join(tid1, NULL)) != 0) {
        perror_die("ERROR pthread_join");
    }
    if ((errno = pthread_join(tid2, NULL)) != 0) {
        perror_die("ERROR pthread_join");
    }

    printf("The value of common resource: %d\n", common);
    if ((errno = pthread_mutex_destroy(&lock)) != 0) {
        perror_die("ERROR pthread_mutex_destroy");
    }

    return EXIT_SUCCESS;
}