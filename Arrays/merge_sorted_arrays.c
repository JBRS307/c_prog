#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define MAX_ARRAYS 5
#define MAX_ARRAY_SIZE 20

// Prints message to stderr and exits with failure code
void die(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

// Check if array is sorted
bool is_sorted(const int* arr, size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

// Fill arrays with user input data
void fill_arrays(int** arrays, int n_arrays, const size_t* sizes) {
    for (int i = 0; i < n_arrays; i++) {
        printf("Give elements of array %d\n", i);
        for (size_t j = 0; j < sizes[i]; j++) {
            scanf("%d", &arrays[i][j]);
        }
        putchar('\n');
        if (!is_sorted((const int*)arrays[i], sizes[i])) {
            die("Array %d is not sorted!\n", i);
        }
    }
}

int main() {
    int n_arrays;
    printf("Give number of arrays to merge: ");
    scanf("%d", &n_arrays);
    if (n_arrays > MAX_ARRAYS || n_arrays <= 0) {
        die("Invalid number of arrays: %d\n", n_arrays);
    }

    size_t sizes[MAX_ARRAYS];
    int* arrays[MAX_ARRAYS];
    printf("Give arrays sizes\n");
    for (int i = 0; i < n_arrays; i++) {
        printf("%d. ", i);
        scanf("%lu", &sizes[i]);
        arrays[i] = (int*)malloc(sizes[i] * sizeof(int));
    }

    fill_arrays(arrays, n_arrays, (const size_t*)sizes);


    return EXIT_SUCCESS;
}