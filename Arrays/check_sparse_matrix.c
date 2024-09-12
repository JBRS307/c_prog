#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define MAX_SIZE 10

// Print given printf like input to stderr and exit
// with failure code
void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

// Returns dynamically allocated matrix of given size
int** create_matrix(size_t rows, size_t cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        die("Malloc error!\n");
    }
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            die("Malloc error!\n");
        }
    }
    return matrix;
}

// Fills matrix with user input
void fill_matrix(int** matrix, size_t rows, size_t cols) {
    printf("Type matrix elements!\n");
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    putchar('\n');
}

// Prints given matrix to stdout
void print_matrix(const int** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        putchar('\n');
    }
}

// Check if matrix is sparse (more zeros than non-zeros)
bool check_sparse(const int** matrix, size_t rows, size_t cols) {
    unsigned long zeros = 0;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeros++;
            }
        }
    }

    return zeros > (rows * cols) / 2;
}

int main() {
    size_t rows, cols;
    printf("Enter matrix dimensions (max is 10 for each dimension)\n");
    scanf("%lu%lu", &rows, &cols);
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        die("Incorrect dimensions!\n");
    }

    int** matrix = create_matrix(rows, cols);
    fill_matrix(matrix, rows, cols);
    print_matrix((const int**)matrix, rows, cols);

    if (check_sparse((const int**)matrix, rows, cols)) {
        printf("Matrix is sparse\n");
    } else {
        printf("Matrix is NOT sparse\n");
    }

    return EXIT_SUCCESS;
}