// Code to show how conditional compilation works
#include <stdio.h>
#include <stdlib.h>

#define QUANTITY 10
#define FESTIVAL 0.02
#define DISCOUNT_COUPON 0.02
#define KINDLE 0.02

int main() {
    double price;
    printf("Enter price: ");
    scanf("%lf", &price);

    double discount;
    #if QUANTITY >= 10
        discount = 0.15;
    #elif QUANTITY >= 5
        discount = 0.10;
    #else
        discount = 0.05;
    #endif

    double total_amount = QUANTITY * price;
    double after_discount = total_amount - total_amount * discount;

    #ifdef FESTIVAL
        after_discount = after_discount - after_discount * FESTIVAL;
    #endif

    return EXIT_SUCCESS;
}