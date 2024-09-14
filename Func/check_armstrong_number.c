#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Get number of digits of an integer
int n_digits(int n) {
    if (n == 0) {
        return 1;
    }

    int digits = 0;
    while (n != 0) {
        digits++;
        n /= 10;
    }
    return digits;
}

bool check_armstrong(const int n) {
    int digits = n_digits(n);

    if (n == 0) {
        return true;
    }

    int curr = n;
    int sum = 0;
    while (curr != 0) {
        int last = curr % 10;
        sum += (int)pow((double)last, (double)digits);
        curr /= 10;
    }
    return sum == n;
}

int main() {
    int n;
    printf("Give integer to check: ");
    scanf("%d", &n);

    if (check_armstrong(n)) {
        printf("%d is an Armstrong number\n", n);
    } else {
        printf("%d is NOT an Armstrong number\n", n);
    }

    return EXIT_SUCCESS;
}