#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int orderid;
    char name[20];
    float amount;
} Customer;

static_assert(sizeof(Customer) == 28, "Structure takes unexpected number of bytes");

int main() {
    printf("sizeof(double): %lu\n", sizeof(double));
    printf("sizeof(float): %lu\n", sizeof(float));
    printf("sizeof(Customer): %lu\n", sizeof(Customer));

    return EXIT_SUCCESS;
}