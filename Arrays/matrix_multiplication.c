#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MIN_RANGE (-10)
#define MAX_RANGE 10

void set_dimensions(int* rows, int* cols) {
    printf("Rows: ");
    scanf("%d", rows);
    printf("Cols: ");
    scanf("%d", cols);
}

// Returns pointer to dynamically allocated matrix filled with pseudorandom numbers.
// Has to be freed after usage.
int** generate_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (MAX_RANGE -  MIN_RANGE + 1) + MIN_RANGE;
        }
    }
    
    return matrix;
}

// Multiplies matrix A by matrix B
// Returns pointer to dynamically allocated matrix, has to be freed after usage
int** matmul(const int** mat_a, int a_rows, int a_cols,
             const int** mat_b, int b_rows, int b_cols) {
    assert(b_rows == a_cols);
    
    int** matrix = (int**)malloc(a_rows * sizeof(int*));
    for (int i = 0; i < a_rows; i++) {
        matrix[i] = (int*)calloc(b_cols, sizeof(int));
    }

    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            for (int k = 0; k < a_cols; k++) {
                matrix[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }

    return matrix;
}

// Prints given matrix to stdout
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        putchar('\n');
    }
}

// Frees given dynamically allocated matrix
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    srand(time(NULL));

    int a_rows, a_cols;
    int b_rows, b_cols;

    printf("Matrix A dimensions\n");
    set_dimensions(&a_rows, &a_cols);

    printf("Matrix B dimensoins\n");
    set_dimensions(&b_rows, &b_cols);

    if (a_cols != b_rows) {
        fprintf(stderr, "Number of columns of matrix A "
        "is not equal to number of rows of matrix B\n");
        return EXIT_FAILURE;
    }

    int** mat_a = generate_matrix(a_rows, a_cols);
    int** mat_b = generate_matrix(b_rows, b_cols);

    print_matrix(mat_a, a_rows, a_cols);
    putchar('\n');
    print_matrix(mat_b, b_rows, b_cols);
    putchar('\n');


    int** new_matrix = matmul((const int**)mat_a, a_rows, a_cols,
                              (const int**)mat_b, b_rows, b_cols);

    print_matrix(new_matrix, a_rows, b_cols);

    free_matrix(mat_a, a_rows);
    free_matrix(mat_b, b_rows);
    free_matrix(new_matrix, a_rows);

    return EXIT_SUCCESS;
}