#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Checks if element d exists in array arr of size n
bool exists(int* arr, int n, int d) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == d) {
            return true;
        }
    }
    return false;
}

int main() {
    srand(time(NULL));

    size_t n_first, n_second;

    printf("Size of first array: ");
    scanf("%lu", &n_first);
    printf("Size of second array: ");
    scanf("%lu", &n_second);

    size_t size_common = n_first <= n_second ? n_first : n_second;

    return EXIT_SUCCESS;
}