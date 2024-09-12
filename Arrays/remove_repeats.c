#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RANGE_MIN (-20)
#define RANGE_MAX 20

// generates random array of size n
// returns pointer to dynamically allocated array
int* generate_random_array(size_t n) {
    int* arr = (int*)malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN;
    }
    return arr;
}

// Returns pointer to newly created, dynamically allocated array with unique
// elements of array arr. Saves size of the new array in n_unique
int* remove_repeats(int* arr, size_t n, size_t* n_unique) {
    int* unique = (int*)malloc(n * sizeof(int));
    *n_unique = 0;

    for (size_t i = 0; i < n; i++) {
        bool unique_elem = true;
        for (size_t j = 0; j < *n_unique; j++) {
            if (arr[i] == unique[j]) {
                unique_elem = false;
                break;
            }
        }
        if (unique_elem) {
            unique[*n_unique] = arr[i];
            (*n_unique)++;
        }
    }

    return (int*)realloc((void*)unique, *n_unique * sizeof(int));    
}

// Prints array of integers of size n to stdout
void print_arr(int* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main() {
    srand(time(NULL));
    // size of array
    size_t n;
    printf("Give size of array: ");
    scanf("%lu", &n);

    int* arr = generate_random_array(n);
    print_arr(arr, n);

    size_t n_unique;
    int* unique = remove_repeats(arr, n, &n_unique);
    print_arr(unique, n_unique);

    free(arr);
    free(unique);
    
    return EXIT_SUCCESS;
}