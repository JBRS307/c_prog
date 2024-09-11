#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RANGE_MIN (-20)
#define RANGE_MAX 20

// Checks if element d exists in array arr of size n
bool exists(int* arr, size_t n, int d) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == d) {
            return true;
        }
    }
    return false;
}

// Generates array filled with pseudorandom numbers of size n.
// Returns dynamically allocated pointer, has to be freed.
int* generate_random_array(size_t n) {
    int* arr = (int*)malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN;
    }
    return arr;
}

// Finds common elements from both arrays and puts these elements in new dynamically
// allocated array. Returns pointer to it. In pointer common_size is saved size of
// array of common elements
int* find_common_elements(int* first, size_t n_first, int* second, size_t n_second, size_t* common_size) {
    size_t n_new = n_first <= n_second ? n_first : n_second;

    int* common_arr = (int*)malloc(n_new * sizeof(int));

    *common_size = 0;

    for (size_t i = 0; i < n_first; i++) {
        if (exists(second, n_second, first[i]) &&
            !exists(common_arr, *common_size, first[i])) {
            common_arr[*common_size] = first[i];
            (*common_size)++;
        }
    }

    return (int*)realloc((void*)common_arr, *common_size * sizeof(int));
}

// Prints array of size n to stdout
void print_arr(int* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main() {
    srand(time(NULL));

    size_t n_first, n_second;

    printf("Size of first array: ");
    scanf("%lu", &n_first);
    printf("Size of second array: ");
    scanf("%lu", &n_second);

    int* first = generate_random_array(n_first);
    int* second = generate_random_array(n_second);

    print_arr(first, n_first);
    print_arr(second, n_second);
    putchar('\n');

    size_t common_size;
    int* common_arr = find_common_elements(first, n_first, second, n_second, &common_size);

    print_arr(common_arr, common_size);

    free(first);
    free(second);
    free(common_arr);

    return EXIT_SUCCESS;
}