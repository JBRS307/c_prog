#include <stdio.h>
#include <stdlib.h>

// Returns GCD of x and y
int gcd(int x, int y) {
    if (y == 0) {
        return x;
    } else if (x % y == 0) {
        return y;
    } else {
        return gcd(y, x % y);
    }
}

// Swaps two integers
void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
} 

int main() {
    int x, y;
    printf("Give numbers x and y to find GCD for\n");
    scanf("%d%d", &x, &y);

    if (x < y) {
        swap_int(&x, &y);
    }

    printf("The GCD of x and y is %d\n", gcd(x, y));

    return EXIT_SUCCESS;
}