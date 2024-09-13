#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

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

// Sums array of size_t values
size_t sum_sizes(const size_t* sizes, int n_arrays) {
    size_t res = 0;
    for (int i = 0; i < n_arrays; i++) {
        res += sizes[i];
    }
    return res;
}

// Returns smallest element of the elements in arrays pointed to by pointers
int pick_smallest(const int** arrays, int n_arrays, size_t* pointers, const size_t* sizes) {
    int smallest = INT_MAX;
    int smallest_index = -1;
    for (int i = 0; i < n_arrays; i++) {
        if (pointers[i] < sizes[i] && arrays[i][pointers[i]] < smallest) {
            smallest_index = i;
            smallest = arrays[i][pointers[i]];
        }
    }

    pointers[smallest_index]++;
    return smallest;
}

// Merges sorted arrays sorted in arrays variable.
// Returns pointer to new dynamically allocated array and saves new size to new_size
int* merge_sorted_arrays(const int** arrays, int n_arrays, const size_t* sizes, size_t* new_size) {
    size_t pointers[MAX_ARRAYS] = {0};

    *new_size = sum_sizes(sizes, n_arrays);
    int* arr = (int*)malloc(*new_size * sizeof(int));

    for (size_t i = 0; i < *new_size; i++) {
        arr[i] = pick_smallest(arrays, n_arrays, pointers, sizes);
    }

    return arr;
}

// Prints array of size n to stdout
void print_arr(int* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
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

    size_t new_size;
    int* merged = merge_sorted_arrays((const int**)arrays, n_arrays, (const size_t*)sizes, &new_size);

    print_arr(merged, new_size);

    for (int i = 0; i < n_arrays; i++) {
        free(arrays[i]);
    }
    free(merged);

    return EXIT_SUCCESS;
}