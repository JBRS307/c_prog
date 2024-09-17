#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double arr_avg(int* arr, size_t n) {
    assert(arr != NULL && "Pointer arr cannot be null");
    
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;

}

int main() {
    size_t n;
    printf("How many elements in array: ");
    scanf("%lu", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter array elements:\n");
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Average of elements: %lf\n", arr_avg(arr, n));

    return EXIT_SUCCESS;
}