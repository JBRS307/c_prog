#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#define RANGE_MIN -2137
#define RANGE_MAX 2137

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

// Returns pointer to max element of an array
int* max_arr(int* arr, size_t n) {
    int* max = arr;

    arr++;
    for (size_t i = 1; i < n; i++, arr++) {
        if (*arr > *max) {
            max = arr;
        }
    }

    return max;
}

// Fills int array with random elements
void fill_arr(int* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN;
    }
}

void print_arr(int* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main() {
    srand(time(NULL));
    size_t n;
    printf("Enter array size: ");
    if (scanf("%lu", &n) == 0) {
        die("Incorrect input!\n");
    }

    int* arr = (int*)malloc(n * sizeof(int));

    fill_arr(arr, n);
    print_arr(arr, n);

    int max_elem = *(max_arr(arr, n));
    printf("Max element of array is %d\n", max_elem);

    free(arr);

    return EXIT_SUCCESS;
}