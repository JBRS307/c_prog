#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

void perror_die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int passengers;

    printf("Enter number of passengers: ");
    scanf("%d", &passengers);
    assert(passengers > 0 && "Number of passengers should be positive integer!");

    int clean_buf = 0;
    while ((clean_buf = getchar()) != '\n' && clean_buf != EOF); // Clearing the stdin
    char* from = NULL;
    char* to = NULL;
    size_t b_from = 0, b_to = 0;
    ssize_t s_from, s_to;

    printf("Enter flight starting point: ");
    if ((s_from = getline(&from, &b_from, stdin)) < 0) {
        perror_die("ERROR getline");
    }

    printf("Enter flight destination: ");
    if ((s_to = getline(&to, &b_to, stdin)) < 0) {
        perror_die("ERROR getline");
    }

    assert(isupper(from[0]) && isupper(to[0]) && "Cities should start with capital letter");
    from[s_from - 1] = '\0';
    to[s_to - 1] = '\0';

    printf("%s %s\n", from, to);

    return EXIT_SUCCESS;
}