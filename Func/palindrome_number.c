#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Counts digits of an integer n
int count_digits(int n) {
    int digits = 0;
    do {
        digits++;
        n /= 10;
    } while (n != 0);
    return digits;
}

// Checks whether integer n is a palindrome number
bool is_palindrome(const int n) {
    int quot = abs(n);
    int new = 0;

    int digits = count_digits(n);
    digits--;

    while (quot > 0) {
        int rem = quot % 10;
        quot /= 10;

        new += (int)(rem * pow(10.0, (double)(digits--)));
    }

    if (n < 0) {
        new *= -1;
    }
    return new == n;
}

int main() {
    int n;
    printf("Type your number: ");
    scanf("%d", &n);

    if (is_palindrome(n)) {
        printf("%d is a palindrome number!\n", n);
    } else {
        printf("%d is NOT a palindrome number!\n", n);
    }

    return EXIT_SUCCESS;
}