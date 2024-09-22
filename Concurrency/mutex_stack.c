#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <pthread.h>

#include "stack.h"

pthread_mutex_t stack_lock = PTHREAD_MUTEX_INITIALIZER;

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

void* thread_push(void* stack_ptr) {
    pthread_mutex_lock(&stack_lock);
    Stack* stack = (Stack*)stack_ptr;
    int data;
    printf("Enter value to push: ");
    if (scanf("%d", &data) != 1) {
        fprintf(stderr, "Invalid input, data not pushed!\n");
        pthread_mutex_unlock(&stack_lock);
        return NULL;
    }
    
    stack_push(stack, data);
    pthread_mutex_unlock(&stack_lock);
    return NULL;
}

void* thread_pop(void* stack_ptr) {
    pthread_mutex_lock(&stack_lock);
    Stack* stack = (Stack*)stack_ptr;

    if (stack->size == 0) {
        printf("Stack is empty!\n");
        pthread_mutex_unlock(&stack_lock);
        return NULL;
    }
    int* data = (int*)malloc(sizeof(int));
    if (data == NULL) {
        die("Memory allocation error!\n");
    }
    
    *data = stack_pop(stack);
    pthread_mutex_unlock(&stack_lock);
    return (void*)data;
}

int main() {
    Stack* stack = init_stack();
    pthread_t push1, push2, pop1, pop2;

    if ((errno = pthread_create(&push1, NULL, thread_push, (void*)stack)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_create(&pop1, NULL, thread_pop, (void*)stack)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_create(&push2, NULL, thread_push, (void*)stack)) != 0) {
        perror_die("ERROR pthread_create");
    }
    if ((errno = pthread_create(&pop2, NULL, thread_pop, (void*)stack)) != 0) {
        perror_die("ERROR pthread_create");
    }

    void* pop_ptr;
    int data;
    if ((errno = pthread_join(pop1, &pop_ptr)) != 0) {
        perror_die("ERROR pthread_join");
    }
    if (pop_ptr != NULL) {
        data = *(int*)pop_ptr;
        free(pop_ptr);
    }
    printf("First popped data: %d\n", data);


    if ((errno = pthread_join(pop2, &pop_ptr)) != 0) {
        perror_die("ERROR thread_join");
    }
    if (pop_ptr != NULL) {
        data = *(int*)pop_ptr;
        free(pop_ptr);
    }
    printf("Second popped data: %d\n", data);

    pthread_mutex_destroy(&stack_lock);
    free_stack(stack);
    return EXIT_SUCCESS;
}