#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#define RANGE_MIN 1
#define RANGE_MAX 10

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

// Returns pointer to matrix element
// returns NULL on incorrect value
int* matrix_get_elem(int* matrix, ssize_t row, ssize_t col, size_t rows, size_t columns) {
    if (row < 0 || col < 0 || (size_t)row >= rows || (size_t)col >= columns) {
        fprintf(stderr, "Incorrect coordinates!\n");
        return NULL;
    }

    return matrix + row * columns + col;
}

// Prints matrix to stdout
void print_matrix(int* matrix, size_t rows, size_t columns) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            printf("%d\t", *(matrix + i * columns + j));
        }
        putchar('\n');
    }
}

void print_matrix_transpose(int* matrix, size_t rows, size_t columns) {
    for (size_t j = 0; j < columns; j++) {
        for (size_t i = 0; i < rows; i++) {
            printf("%d\t", *(matrix + i * columns + j));
        }
        putchar('\n');
    }
}

// Fills matrix with random data
void fill_matrix(int* matrix, size_t rows, size_t columns) {
    for (size_t i = 0; i < rows * columns; i++) {
        matrix[i] = rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN;
    }
}

int main() {
    srand(time(NULL));
    ssize_t rows, columns;
    printf("Enter dimensions of your matrix: ");
    if (scanf("%lu%lu", &rows, &columns) != 2) {
        die("Incorrect dimensions!\n");
    }
    if (rows <= 0 || columns <= 0) {
        die("Incorrect dimensions!\n");
    }

    int* matrix = (int*)malloc(rows * columns * sizeof(int));

    fill_matrix(matrix, rows, columns);
    print_matrix(matrix, rows, columns);
    putchar('\n');
    print_matrix_transpose(matrix, rows, columns);

    free(matrix);
    return EXIT_SUCCESS;
}